"""Evaluate one saved candidate on one pinned CoderUJB row; no model calls.

Use system Python with eval-venv site-packages on PYTHONPATH (pyarrow + javalang).
Only the evaluator reads the full row. Model input comes from a separate prompt export.
"""
import argparse
import ast
import fcntl
import hashlib
import json
import os
import re
import shutil
import signal
import subprocess
import tempfile
import time
import xml.etree.ElementTree as ET
from pathlib import Path
from types import SimpleNamespace

import javalang
import pyarrow.parquet as pq

BASE = Path(__file__).resolve().parent
DATA = Path('/data/jianyeshi/coderujb-reproduction')
RUNTIME = DATA / 'runtime'
D4J = RUNTIME / 'defects4j-2.0.1/framework/bin/defects4j'
AUDIT = json.loads((BASE / 'evidence/dataset-audit/audit.json').read_text())
OUTPUT = BASE / 'evidence/scoring'
TASKS = {'FCG': 'complete', 'CTG': 'testgen', 'ITG': 'testgenissue', 'APR': 'repair', 'DD': 'defectdetection'}
ENV = os.environ.copy()
ENV.update(JAVA_HOME=str(RUNTIME / 'jdk8u504-b01'), TZ='America/Los_Angeles', LC_ALL='C.UTF-8')
ENV['PATH'] = ENV['JAVA_HOME'] + '/bin:' + str(D4J.parent) + ':' + ENV['PATH']
ENV['PERL5LIB'] = ':'.join(str(RUNTIME / 'perl-rpm-root' / s) for s in
                           ('usr/share/perl5/vendor_perl', 'usr/lib64/perl5/vendor_perl'))


def sha(data):
    return hashlib.sha256(data).hexdigest()


def save(path, value):
    tmp = path.with_suffix('.tmp')
    tmp.write_text(json.dumps(value, indent=2, ensure_ascii=False) + '\n')
    tmp.replace(path)


def row_at(task, idx):
    data = AUDIT[task]
    if not 0 <= idx < data['n']:
        raise ValueError('row index out of range')
    table = DATA / 'datasets' / (data['repo'].split('/')[1] + '-' + data['revision'] + '.parquet')
    if sha(table.read_bytes()) != data['file_sha256']:
        raise ValueError('dataset differs from frozen input')
    return pq.read_table(table).slice(idx, 1).to_pylist()[0]


def official(task):
    src = BASE / 'ujb/code_ujb/tasks' / ('code_ujb_' + TASKS[task] + '.py')
    helpers = ast.parse((BASE / 'ujb/code_ujb/Task.py').read_text())
    nodes = [x for x in helpers.body if getattr(x, 'name', '') in ('clean_signature', 'remove_line_comment')]
    for x in ast.walk(ast.parse(src.read_text())):
        if isinstance(x, ast.FunctionDef) and x.name in ('_stop_at_function', 'postprocess_chat_generation',
                                                        'postprocess_complete_generation', 'check_defect'):
            x.decorator_list = []
            nodes.append(x)
    ns = {'re': re}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(src), 'exec'), ns)
    return ns


def dd_metrics(categories):
    counts = {k: categories.count(k) for k in ('tp', 'tn', 'fp', 'fn', 'error')}
    tp, tn, fp, fn, error = (counts[k] for k in ('tp', 'tn', 'fp', 'fn', 'error'))
    total = sum(counts.values())
    def ratio(num, den):
        return num / den if den else None
    precision = ratio(tp, tp + fp)
    recall = ratio(tp, tp + fn)
    f1 = ratio(2 * precision * recall, precision + recall) if None not in (precision, recall) else None
    return dict(counts, total=total, correct=tp+tn, acc=ratio(tp+tn, total-error),
                acc_w_error=ratio(tp+tn, total), precision=precision, recall=recall, f1=f1)


class Verdict(Exception):
    def __init__(self, status, reason):
        super().__init__(reason)
        self.status = status


def run(directory, name, argv, timeout, env):
    started = time.monotonic()
    out = directory / (name + '.stdout.log')
    err = directory / (name + '.stderr.log')
    timed_out = False
    with out.open('wb') as stdout, err.open('wb') as stderr:
        proc = subprocess.Popen(argv, env=env, cwd=directory, stdout=stdout, stderr=stderr, start_new_session=True)
        try:
            proc.wait(timeout=timeout)
        except subprocess.TimeoutExpired:
            timed_out = True
            os.killpg(proc.pid, signal.SIGKILL)
            proc.wait()
    rec = dict(name=name, argv=list(map(str, argv)), exit_code=proc.returncode, timeout=timed_out,
               elapsed_seconds=round(time.monotonic()-started, 3), stdout=out.name, stderr=err.name)
    return rec, out.read_text(errors='replace'), err.read_text(errors='replace')


def score_java(task, row, patch, directory, work, report):
    tmp = work / 'tmp'
    tmp.mkdir()
    env = dict(ENV, TMPDIR=str(tmp), TMP=str(tmp), TEMP=str(tmp))
    tests = [row['testmethod']] if task == 'ITG' else row['testmethods']
    if task == 'CTG':
        tests = tests[:1]
    if not tests:
        raise Verdict('infrastructure_unresolved', 'missing test selection')

    def command(name, args):
        rec, stdout, stderr = run(directory, name, [D4J, *args], 240 if name == 'suite' else 180, env)
        report['commands'].append(rec)
        if rec['timeout']:
            raise Verdict('timeout_unresolved', name)
        if rec['exit_code']:
            if name.endswith('compile') and re.search(r'\[javac\].*' + re.escape(target.name) + r':\d+: error:', stderr + stdout):
                raise Verdict('fail', 'candidate_compile')
            raise Verdict('infrastructure_unresolved', name)
        return stdout

    def test(name, checkout, case=None):
        failures = checkout / 'failing_tests'
        failures.unlink(missing_ok=True)
        stdout = command(name, ['test', '-w', checkout] + (['-t', case] if case else []))
        count = re.search(r'^Failing tests:\s*(\d+)\s*$', stdout, re.M)
        if not count or not failures.is_file():
            raise Verdict('infrastructure_unresolved', name + ': missing JUnit verdict')
        detail = failures.read_text(errors='replace')
        (directory / (name + '.failing_tests.txt')).write_text(detail)
        reported = re.findall(r'^--- (.+)$', detail, re.M)
        if int(count[1]) != len(reported):
            raise Verdict('infrastructure_unresolved', name + ': inconsistent JUnit verdict')
        report['tests'][name] = {'selected': case, 'failed': reported}
        return reported

    for variant in (['fixed', 'buggy'] if task == 'ITG' else ['fixed']):
        checkout = work / variant
        suffix = '_' + variant if task == 'ITG' else ''
        version = str(row['bug_id']) + ('b' if variant == 'buggy' else 'f')
        command(variant + '-checkout', ['checkout', '-p', row['project'], '-v', version, '-w', checkout])
        target = checkout / row['location' + suffix]
        if not target.resolve().is_relative_to(checkout) or not target.is_file():
            raise Verdict('infrastructure_unresolved', 'invalid injection path')
        source = row['source' + suffix].split('\n')
        start, end = row['start'+suffix], row['end'+suffix]
        if not 0 <= start <= end < len(source):
            raise Verdict('infrastructure_unresolved', 'invalid injection range')
        candidate = '\n'.join(source[:start] + patch.split('\n') + source[end+1:])
        try:
            javalang.parse.parse(candidate)
        except (javalang.parser.JavaSyntaxError, javalang.tokenizer.LexerError):
            # A parser limitation in the supplied class also affects the original.
            try:
                javalang.parse.parse('\n'.join(source))
            except (javalang.parser.JavaSyntaxError, javalang.tokenizer.LexerError):
                raise Verdict('infrastructure_unresolved', 'upstream parser rejected supplied class')
            raise Verdict('fail', 'candidate_syntax')
        target.write_text(candidate)
        command(variant + '-compile', ['compile', '-w', checkout])
        for i, case in enumerate(tests):
            failed = test(variant + '-test-' + str(i), checkout, case.strip())
            if variant == 'buggy':
                if not failed:
                    raise Verdict('fail', 'test did not detect buggy version')
                trace = (directory / f'{variant}-test-{i}.failing_tests.txt').read_text()
                frame = r'^\s*at ' + re.escape(case.strip().replace('::','.')) + r'\('
                if failed != [case.strip()] or not re.search(frame, trace, re.M):
                    raise Verdict('infrastructure_unresolved', 'unexpected failing method / stack')
            elif failed:
                if case.strip() not in failed:
                    raise Verdict('infrastructure_unresolved', 'unexpected failing test')
                raise Verdict('fail', 'target test failed')
        if task in ('APR', 'FCG'):
            if test('suite', checkout):
                raise Verdict('fail', 'project suite failed')
        elif variant == 'fixed':
            classes = (row['classes_modified'] if task == 'ITG' else
                       sorted({entry['be_test_class_name'] for entry in row['classmethods']}))
            increment = directory / 'instrument-classes.txt'
            increment.write_text('\n'.join(classes) + '\n')
            stdout = command('coverage', ['coverage', '-w', checkout, '-t', tests[0].strip(), '-i', increment])
            xml = checkout / 'coverage.xml'
            line = re.search(r'^[ \t]*Line coverage:\s*([\d.]+)%', stdout, re.M)
            cond = re.search(r'^[ \t]*Condition coverage:\s*([\d.]+)%', stdout, re.M)
            if 'WARNING: Some tests failed' in (directory / 'coverage.stderr.log').read_text():
                raise Verdict('infrastructure_unresolved', 'test failed under instrumentation')
            if not xml.exists() or not line or not cond:
                raise Verdict('infrastructure_unresolved', 'incomplete coverage output')
            shutil.copyfile(xml, directory / 'coverage.xml')
            root = ET.parse(xml)
            direct_hits = sum(int(x.get('hits', '0')) > 0 for c in root.findall('.//class')
                              if c.get('name') in classes for x in c.findall('./lines/line'))
            # Match the official aggregate coverage gate, including instrumented inner classes.
            hits = sum(int(x.get('hits', '0')) > 0 for c in root.findall('.//class')
                       for x in c.findall('./lines/line'))
            report['coverage'] = dict(classes=classes, line_pct=float(line[1]),
                                      condition_pct=float(cond[1]), instrumented_lines_hit=hits,
                                      direct_target_lines_hit=direct_hits,
                                      instrumented_xml_classes=[c.get('name') for c in root.findall('.//class')])
    if task in ('CTG', 'ITG') and (not report['coverage']['instrumented_lines_hit'] or
                                  report['coverage']['line_pct'] == 0):
        raise Verdict('fail', 'zero target coverage')


def evaluate(task, idx, raw, mode, origin, retry=False):
    row = row_at(task, idx)
    revision = AUDIT[task]['revision']
    upstream = BASE / 'ujb/code_ujb/tasks' / ('code_ujb_' + TASKS[task] + '.py')
    identity = dict(task=task, revision=revision, task_idx=idx, task_id=row['task_id'], origin=origin,
                    mode=mode, raw_sha256=sha(raw.encode()), scorer_sha256=sha(Path(__file__).read_bytes()),
                    upstream_sha256=sha(upstream.read_bytes()), d4j_revision=subprocess.check_output(
                        ['git','-C',D4J.parents[2],'rev-parse','HEAD'], text=True).strip())
    key = sha(json.dumps(identity, sort_keys=True).encode())
    group = OUTPUT / origin / f'{task}-{idx}-{revision[:8]}' / key
    group.mkdir(parents=True, exist_ok=True)
    with (group / 'lock').open('a') as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        attempts = sorted(group.glob('attempt-*'))
        if attempts:
            prev = attempts[-1] / 'result.json'
            if prev.exists():
                record = json.loads(prev.read_text())
                if record['status'] not in ('running', 'timeout_unresolved', 'infrastructure_unresolved'):
                    return prev
                if not retry or len(attempts) >= 2:
                    return prev
            elif not retry or len(attempts) >= 2:
                raise RuntimeError('incomplete attempt; explicit bounded retry required')
        directory = group / f'attempt-{len(attempts)+1}'
        directory.mkdir()
        result = directory / 'result.json'
        rec = dict(identity, project=row['project'], bug_id=row['bug_id'], status='running', commands=[], tests={})
        save(result, rec)
        (directory / 'raw.txt').write_text(raw)
        try:
            ns = official(task)
            obj = SimpleNamespace(dataset={'train': {idx: row}}, _stop_at_function=ns['_stop_at_function'])
            patch = raw if mode == 'extracted' else ns['postprocess_'+mode+'_generation'](obj, raw, idx)
            (directory / 'candidate.txt').write_text(patch)
            if task == 'DD':
                pred, _ = ns['check_defect'](patch)
                cat = ('error' if pred == 'error' else ('tp' if row['defective'] else 'fp') if
                       pred == 'defect' else ('fn' if row['defective'] else 'tn'))
                rec.update(category=cat, metrics=dd_metrics([cat]), status='pass' if cat in ('tp','tn') else 'fail')
            elif patch.startswith('Can not find target function in answer!'):
                raise Verdict('fail', 'official extraction missing target function')
            else:
                with tempfile.TemporaryDirectory(dir=DATA/'worktrees', prefix=f'{task}-{idx}-') as work:
                    score_java(task, row, patch, directory, Path(work), rec)
                rec['status'] = 'pass'
        except Verdict as exc:
            rec.update(status=exc.status, reason=str(exc))
        except (ValueError, OSError, ET.ParseError, RecursionError) as exc:
            rec.update(status='infrastructure_unresolved', reason=repr(exc))
        save(result, rec)
        return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('task', choices=TASKS)
    parser.add_argument('idx', type=int)
    parser.add_argument('file', type=Path)
    parser.add_argument('--mode', choices=['chat','complete','extracted'], default='chat',
                        help='complete expects official prompt concatenated with the raw continuation')
    parser.add_argument('--origin', choices=['model','scorer_control'], required=True)
    parser.add_argument('--retry', action='store_true', help='Retry an unresolved attempt once')
    args = parser.parse_args()
    print(evaluate(args.task, args.idx, args.file.read_text(), args.mode, args.origin, args.retry))
