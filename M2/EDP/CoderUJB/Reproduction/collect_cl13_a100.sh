#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
export PYTHONPATH=/data/jianyeshi/coderujb-reproduction/runtime/eval-venv/lib/python3.14/site-packages PYTHONDONTWRITEBYTECODE=1
dir=evidence/cl13-a100
remote=$(cat "$dir/remote.txt")
job=$(cat "$dir/slurm-id.txt")
[[ "$remote" =~ ^/scratch_p/hibouwu/coderujb/cl13-a100-[[:alnum:]]+$ && "$job" =~ ^[0-9]+$ ]]
exec 8>"$dir/collection.lock"
flock -n 8
while true; do
  state=$(ssh -o BatchMode=yes romeo "sacct -Xj $job -nPo State" | head -1)
  rsync -aq --exclude='*.tmp' "romeo:$remote/" "$dir/"
  python3 -u score_cl13_a100.py
  case "$state" in COMPLETED*|CANCELLED*|FAILED*|NODE_FAIL*|OUT_OF_MEMORY*|TIMEOUT*|PREEMPTED*) break;; esac
  sleep 30
done
ssh -o BatchMode=yes romeo "sacct -j $job -P -o JobID,State,ExitCode,Elapsed,AllocTRES,MaxRSS" >"$dir/slurm-accounting.txt"
ssh -o BatchMode=yes romeo "cd $remote && find . -type f -print0 | sort -z | xargs -0 sha256sum" >"$dir/remote-sha256.txt"
rsync -aq "romeo:$remote/" "$dir/"
(cd "$dir"; sha256sum -c remote-sha256.txt >verification.log)
python3 -u score_cl13_a100.py
