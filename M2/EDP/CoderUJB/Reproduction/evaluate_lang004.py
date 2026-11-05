#!/usr/bin/env python3
"""Evaluate a saved completion or chat answer for FCG task 4, with a baseline.

Run with the isolated eval-venv Python. Uses the official function-boundary
extractor and source replacement, with explicit baseline and command logs.
This single-sample runner does not compute benchmark-level pass@k.
"""
import argparse
import ast
import datetime
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import signal
import subprocess
import tempfile
import time
from types import SimpleNamespace

import javalang


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--runtime', type=Path,
                        default=Path('/data/jianyeshi/coderujb-reproduction/runtime'))
    parser.add_argument('--chat-answer', type=Path, help='Use official chat extraction on this final answer.')
    args = parser.parse_args()
    base = Path(__file__).resolve().parent
    stamp = datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
    evidence = base / 'evidence' / ('lang004-evaluation-' + stamp)
    evidence.mkdir(exist_ok=False)
    work_parent = args.runtime.parent / 'worktrees'
    work_parent.mkdir(exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix='lang004-' + stamp + '-', dir=work_parent))
    d4j = args.runtime / 'defects4j-2.0.1/framework/bin/defects4j'
    env = os.environ.copy()
    env['JAVA_HOME'] = str(args.runtime / 'jdk8u504-b01')
    env['PATH'] = env['JAVA_HOME'] + '/bin:' + str(d4j.parent) + ':' + env['PATH']
    env['PERL5LIB'] = ':'.join(str(args.runtime / 'perl-rpm-root' / x) for x in
                             ['usr/share/perl5/vendor_perl', 'usr/lib64/perl5/vendor_perl'])
    env['TZ'] = 'America/Los_Angeles'
    # Set explicitly, as in the Defects4J Java-8 generation of the framework.
    env['LC_ALL'] = 'C.UTF-8'
    result = {'status': 'running', 'task_idx': 4, 'sample_count': 1,
              'benchmark_metric_computed': False, 'work_directory': str(work),
              'evidence_directory': str(evidence), 'environment': {
                  k: env[k] for k in ['JAVA_HOME', 'PERL5LIB', 'TZ', 'LC_ALL']},
              'commands': [], 'baseline': {}, 'model': {}}

    def save():
        (evidence / 'result.json').write_text(json.dumps(result, indent=2) + '\n')

    def run(name, command, timeout, cwd=None, test=False):
        started = time.monotonic()
        out_path, err_path = evidence / (name + '.stdout.log'), evidence / (name + '.stderr.log')
        timed_out = False
        with out_path.open('wb') as out, err_path.open('wb') as err:
            proc = subprocess.Popen([str(x) for x in command], cwd=cwd, env=env,
                                    stdout=out, stderr=err, start_new_session=True)
            try:
                code = proc.wait(timeout=timeout)
            except subprocess.TimeoutExpired:
                timed_out = True
                os.killpg(proc.pid, signal.SIGTERM)
                try:
                    code = proc.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    os.killpg(proc.pid, signal.SIGKILL)
                    code = proc.wait()
        stdout = out_path.read_text(errors='replace')
        rec = {'name': name, 'argv': [str(x) for x in command], 'exit_code': code,
               'timed_out': timed_out, 'elapsed_seconds': time.monotonic() - started,
               'stdout': out_path.name, 'stderr': err_path.name}
        matches = re.findall(r'^Failing tests:\s*(\d+)\s*$', stdout, re.M)
        rec['passed'] = not timed_out and code == 0
        if test:
            rec['failing_tests'] = int(matches[-1]) if matches else None
            rec['passed'] &= bool(matches) and int(matches[-1]) == 0
            failing = Path(cwd) / 'failing_tests'
            if failing.exists():
                shutil.copyfile(failing, evidence / (name + '.failing_tests.txt'))
        result['commands'].append(rec)
        save()
        print(json.dumps(rec), flush=True)
        return rec

    save()
    try:
        for label, binary in [('java-version', 'java'), ('javac-version', 'javac')]:
            if not run(label, [Path(env['JAVA_HOME']) / 'bin' / binary, '-version'], 15)['passed']:
                raise RuntimeError('Java version command failed')
        result['defects4j_commit'] = subprocess.check_output(
            ['git', '-C', str(d4j.parents[2]), 'rev-parse', 'HEAD'], text=True).strip()
        official = base / 'ujb/code_ujb/tasks/code_ujb_complete.py'
        result['official_task_source_sha256'] = sha(official.read_bytes())
        module = ast.parse(official.read_text())
        task_class = next(n for n in module.body if isinstance(n, ast.ClassDef)
                          and n.name == 'CodeUJBComplete')
        function = next(n for n in task_class.body if isinstance(n, ast.FunctionDef)
                        and n.name == '_stop_at_function')
        function.decorator_list = []
        namespace = {}
        exec(compile(ast.Module(body=[function], type_ignores=[]), str(official), 'exec'), namespace)
        row = json.loads((base / 'data_preview/fcg-first8.json').read_text())['rows'][4]['row']
        if args.chat_answer:
            raw = args.chat_answer.read_text()
            prompt = (base / 'sample_pack/prompts/004_Lang.txt').read_text()
            assert prompt.strip() == row['prompt_chat'].strip()
            task_module = ast.parse((base / 'ujb/code_ujb/Task.py').read_text())
            helpers = [n for n in task_module.body if isinstance(n, ast.FunctionDef)
                       and n.name in ('clean_signature', 'remove_line_comment')]
            chat = next(n for n in task_class.body if isinstance(n, ast.FunctionDef)
                        and n.name == 'postprocess_chat_generation')
            exec(compile(ast.Module(body=helpers + [chat], type_ignores=[]), str(official), 'exec'), namespace)
            task = SimpleNamespace(dataset={'train': {4: row}}, _stop_at_function=namespace['_stop_at_function'])
            completion = namespace['postprocess_chat_generation'](task, raw, 4)
            result.update(generation_mode='chat', raw_answer_file=str(args.chat_answer.resolve()))
        else:
            raw = (base / 'evidence/romeo-model-probe-generation.txt').read_text()
            prompt = (base / 'sample_pack/prompts_complete/004_Lang.txt').read_text()
            assert prompt == row['prompt_complete']
            completion = namespace['_stop_at_function'](
                (prompt + raw)[len(row['prompt_complete_with_comment']):])
            result['generation_mode'] = 'complete'
        lines = row['source'].split('\n')
        assert '\n'.join(lines[row['start']:row['end'] + 1]) == row['function']
        patched = '\n'.join(lines[:row['start']] + completion.split('\n') + lines[row['end'] + 1:])
        (evidence / 'generated-function.java').write_text(completion + '\n')
        (evidence / 'reference-function.java').write_text(row['function'] + '\n')
        result.update(task_id=row['task_id'], project=row['project'], revision='1f',
                      generated_function_file='generated-function.java',
                      raw_generation_sha256=sha(raw.encode()),
                      prompt_sha256=sha(prompt.encode()),
                      baseline_source_sha256=sha(row['source'].encode()),
                      patched_source_sha256=sha(patched.encode()),
                      processing_note='Official mode-specific extraction and inclusive source-line replacement. No manual edits to the generated function.')

        for variant, source in [('baseline', row['source']), ('model', patched)]:
            state = result[variant]
            checkout = work / variant
            state['worktree'] = str(checkout)
            rec = run(variant + '-checkout', [d4j, 'checkout', '-p', 'Lang', '-v', '1f', '-w', checkout], 180)
            if not rec['passed']:
                result['status'] = 'environment_checkout_failed'
                return
            target = checkout / row['location']
            state['checkout_source_sha256'] = sha(target.read_bytes())
            state['checkout_matches_dataset_source'] = target.read_bytes() == row['source'].encode()
            target.write_text(source)
            try:
                javalang.parse.parse(source)
                state['pass_syntax'] = True
            except Exception as exc:
                state.update(pass_syntax=False, syntax_error=repr(exc))
                result['status'] = 'baseline_syntax_failed' if variant == 'baseline' else 'evaluated_model_syntax_failed'
                return
            rec = run(variant + '-compile', [d4j, 'compile', '-w', checkout], 120)
            state['pass_compile'] = rec['passed']
            if not rec['passed']:
                result['status'] = 'baseline_compile_failed' if variant == 'baseline' else 'evaluated_model_compile_failed'
                return
            state['targeted_tests'] = []
            for i, test in enumerate(row['testmethods']):
                rec = run(variant + '-targeted-' + str(i + 1),
                          [d4j, 'test', '-w', checkout, '-t', test], 120, cwd=checkout, test=True)
                state['targeted_tests'].append({'testmethod': test, 'passed': rec['passed'],
                                               'failing_tests': rec['failing_tests']})
                if not rec['passed']:
                    state['pass_trigger'] = False
                    result['status'] = 'baseline_targeted_failed' if variant == 'baseline' else 'evaluated_model_targeted_failed'
                    return
            state['pass_trigger'] = True
            rec = run(variant + '-all-tests', [d4j, 'test', '-w', checkout], 180, cwd=checkout, test=True)
            state['pass_all'] = rec['passed']
            if not rec['passed']:
                result['status'] = 'baseline_full_suite_failed' if variant == 'baseline' else 'evaluated_model_full_suite_failed'
                return
        result['status'] = 'evaluated_model_passed_all_tests'
    except Exception as exc:
        result['status'] = 'runner_error'
        result['error'] = repr(exc)
        raise
    finally:
        save()
        print('RESULT', evidence / 'result.json', result['status'], flush=True)


if __name__ == '__main__':
    main()
