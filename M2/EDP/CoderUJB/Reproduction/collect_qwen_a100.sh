#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
dir=evidence/qwen-a100
export PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=/data/jianyeshi/coderujb-reproduction/runtime/eval-venv/lib/python3.14/site-packages
remote=$(cat "$dir/remote.txt"); job=$(tail -1 "$dir/jobs.txt")
[[ "$remote" =~ ^/scratch_p/hibouwu/coderujb/qwen-a100-[[:alnum:]]+$ && "$job" =~ ^[0-9]+$ ]]
exec 8>"$dir/collection.lock"; flock -n 8
while true; do
  state=$(ssh -o BatchMode=yes romeo "sacct -Xj $job -nPo State" | head -1)
  rsync -aq --exclude='*.tmp' "romeo:$remote/" "$dir/"
  if ! test -f "$dir/admit-formal"; then
    python3 score_qwen_a100.py --pilot
    if test -s "$dir/pilot-score.json"; then
      python3 - <<'PY'
import json,pathlib
p=pathlib.Path('evidence/qwen-a100')
score=json.loads((p/'pilot-score.json').read_text())
result=pathlib.Path(score['result']);steps=json.loads(result.read_text())
assert score['status'] in ('pass','fail') and (result.parent/'candidate.txt').stat().st_size>0
assert steps['commands'], 'no project execution for pilot'
(p/'gate-receipt.json').write_text(json.dumps({'pilot_row':score['task_idx'],'official_result':score['result'],
    'pilot_status':score['status'],'project_steps':[c['name'] for c in steps['commands']],
    'admission_reason':'Model loaded in BF16, returned final text, and the extracted candidate reached real project evaluation.'},indent=2)+'\n')
PY
      ssh -o BatchMode=yes romeo "touch $remote/admit-formal"
      touch "$dir/admit-formal"
    fi
  fi
  if test -f "$dir/admit-formal"; then python3 -u score_qwen_a100.py; fi
  case "$state" in COMPLETED*|FAILED*|TIMEOUT*|NODE_FAIL*|CANCELLED*|OUT_OF_MEMORY*|PREEMPTED*) break;; esac
  sleep 18
done
ssh -o BatchMode=yes romeo "sacct -j $job -P -o JobID,State,ExitCode,Elapsed,AllocTRES,MaxRSS" >"$dir/slurm-$job.txt"
ssh -o BatchMode=yes romeo "cd $remote && find . -type f -print0 | sort -z | xargs -0 sha256sum" >"$dir/remote-sha256-$job.txt"
rsync -aq "romeo:$remote/" "$dir/"
(cd "$dir"; sha256sum -c "remote-sha256-$job.txt" >"verification-$job.log")
python3 -u score_qwen_a100.py
