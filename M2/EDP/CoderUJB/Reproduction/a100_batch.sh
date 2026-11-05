#!/usr/bin/env bash
# Run an already frozen eligible batch once, verify remote evidence, and evaluate saved outputs locally.
set -euo pipefail
cd "$(dirname "$0")"
export PYTHONPATH=/data/jianyeshi/coderujb-reproduction/runtime/eval-venv/lib/python3.14/site-packages
export PYTHONDONTWRITEBYTECODE=1
root=evidence/oss120-a100
batch=$1
[[ "$batch" =~ ^[a-z0-9-]+$ ]]
dir=$root/batches/$batch
test -s "$dir/inputs.json"
exec 8>"$dir/controller.lock"
flock -n 8
if ! test -s "$dir/remote.txt"; then
  ssh -o BatchMode=yes romeo 'mktemp -d /scratch_p/hibouwu/coderujb/oss120-a100-XXXXXX' >"$dir/remote.txt"
fi
remote=$(cat "$dir/remote.txt")
[[ "$remote" =~ ^/scratch_p/hibouwu/coderujb/oss120-a100-[[:alnum:]]+$ ]]
if ! test -s "$dir/slurm-id.txt"; then
  if test -f "$dir/submit-started"; then
    echo 'Unknown prior submission: inspect Slurm before retry' >&2
    exit 2
  fi
  scp -q "$root"/{infer.py,job.sh,protocol.json} "$dir/inputs.json" evidence/oss120-task-pilot/{manifest.json,stage.py} "romeo:$remote/"
  touch "$dir/submit-started"
  ssh -o BatchMode=yes romeo "cd $remote && sbatch --parsable -A r260073 -p instant --gres=gpu:1 -C armgpu --cpus-per-task=8 --mem=160G --time=00:30:00 -J ujb-oss120-A job.sh" >"$dir/slurm-id.txt"
fi
job=$(cat "$dir/slurm-id.txt")
[[ "$job" =~ ^[0-9]+$ ]]
while true; do
  state=$(ssh -o BatchMode=yes romeo "sacct -Xj $job --noheader -P -o State" | head -1)
  case "$state" in COMPLETED*|CANCELLED*|FAILED*|NODE_FAIL*|OUT_OF_MEMORY*|TIMEOUT*|PREEMPTED*) break;; esac
  sleep 20
done
ssh -o BatchMode=yes romeo "sacct -j $job -P -o JobID,State,ExitCode,Elapsed,AllocTRES,MaxRSS" >"$dir/slurm-accounting.txt"
ssh -o BatchMode=yes romeo "cd $remote && find . -type f -print0 | sort -z | xargs -0 sha256sum" >"$dir/remote-sha256.txt"
scp -qr "romeo:$remote/." "$dir/"
(cd "$dir"; sha256sum -c remote-sha256.txt > verification.log)
cmp "$root/protocol.json" "$dir/protocol.json"
python3 heatmap_a100.py score --batch "$batch"
