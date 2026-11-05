"""Evaluator-side fixtures; never export this data or these files to a model."""
from concurrent.futures import ThreadPoolExecutor
from score_candidate import BASE, OUTPUT, ENV, row_at, dd_metrics, evaluate, run, save
import json
import sys
import time

ROWS = {'FCG':4, 'CTG':10, 'ITG':12, 'APR':6, 'DD':0}


def check(task):
    idx = ROWS[task]
    row = row_at(task, idx)
    if task == 'DD':
        fixtures = [('pass','Yes'), ('fail','No'), ('fail','Inconclusive')]
    else:
        known_good = row['fix'] if task == 'APR' else row['function']
        negatives = {'FCG':'return this;', 'CTG':'throw new AssertionError("negative control");', 'ITG':'StringEscapeUtils.escapeHtml("abc");', 'APR':'throw new IllegalStateException("negative control");'}
        bad = row['function_signature'] + '{ ' + negatives[task] + ' }'
        fixtures = [('pass',known_good), ('fail',bad)]
    outcomes = []
    for expected, raw in fixtures:
        path = evaluate(task, idx, raw, 'chat' if task == 'DD' else 'extracted', 'scorer_control', '--retry' in sys.argv)
        data = json.loads(path.read_text())
        outcomes.append(dict(expected=expected, actual=data['status'], reason=data.get('reason'),
                             path=str(path.relative_to(BASE))))
    return task, outcomes


if __name__ == '__main__':
    OUTPUT.mkdir(parents=True, exist_ok=True)
    with ThreadPoolExecutor(max_workers=2) as pool:
        result = dict(pool.map(check, ROWS))
    save(OUTPUT / 'controls.json', result)
    print(json.dumps(result, indent=2), flush=True)
    assert all(c['actual'] == c['expected'] for items in result.values() for c in items)
    assert dd_metrics(['tp','tn','fn','error'])['acc'] == 2/3
    assert dd_metrics(['fn','tn'])['precision'] is None
    assert dd_metrics(['error'])['acc'] is None
    assert dd_metrics(['error'])['acc_w_error'] == 0
    assert dd_metrics(['fp','fn'])['f1'] is None
    assert dd_metrics([])['acc_w_error'] is None
    # The child ignores SIGTERM; it must never write after the parent's timeout.
    import tempfile
    from pathlib import Path
    with tempfile.TemporaryDirectory() as tmp:
        directory = Path(tmp)
        marker = directory / 'survived'
        child = 'import signal,time,pathlib;signal.signal(signal.SIGTERM,signal.SIG_IGN);time.sleep(1);pathlib.Path(%r).touch()' % str(marker)
        parent = 'import subprocess,sys,time;subprocess.Popen([sys.executable,"-c",%r]);time.sleep(4)' % child
        metadata, _, _ = run(directory,'timeout-fixture',[sys.executable,'-c',parent],0.4,ENV)
        time.sleep(0.8)
        assert metadata['timeout'] and not marker.exists()
        for key in ('stdout', 'stderr'):
            (OUTPUT / metadata[key]).write_bytes((directory / metadata[key]).read_bytes())
        save(OUTPUT / 'timeout-control.json', dict(metadata, child_marker_exists=marker.exists()))
    before = set(OUTPUT.rglob('attempt-*'))
    assert dict(map(check, ROWS)) == result and before == set(OUTPUT.rglob('attempt-*'))
    save(OUTPUT / 'resume-control.json', dict(terminal_attempts_reused=sum(map(len,result.values())), new_attempts=0))
    cases = {'mixed': ['tp','tn','fn','error'], 'no_predicted_positives': ['fn','tn'],
             'all_unparseable':['error','error'], 'false_positive_and_negative':['fp','fn'], 'empty':[]}
    save(OUTPUT / 'dd-metrics-controls.json', {k:dd_metrics(v) for k,v in cases.items()})
