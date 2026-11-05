#!/usr/bin/env bash
set -euo pipefail
root=/scratch_p/hibouwu/coderujb/full20-eval-aeV81g
export CODERUJB_BASE="$root/repro" CODERUJB_DATA="$root/data" CODERUJB_RUN="$root/repro/run"
export CODERUJB_PERL5LIB="$root/data/runtime/perl-local/lib/perl5"
export PATH="/apps/2025/spack_install/linux-rhel9-zen4/linux-rhel9-zen4/gcc-14.2.0/perl-5.40.0-7cjrbpcgin5xh5wdnw2b7tqbtpnjktlj/bin:/apps/2025/spack_install/linux-rhel9-zen4/linux-rhel9-zen4/aocc-5.0.0/subversion-1.14.2-6ithduropjdhvmle3m2c4vazuk4gupvn/bin:$PATH"
export CODERUJB_WORKTREES
CODERUJB_WORKTREES=$(mktemp -d /dev/shm/coderujb-cpu-XXXXXX)
trap 'rm -rf -- "$CODERUJB_WORKTREES"' EXIT
export PYTHONDONTWRITEBYTECODE=1 OMP_NUM_THREADS=1
export JAVA_TOOL_OPTIONS=-XX:ActiveProcessorCount=2
cd "$root/repro"
if [[ "${1:-}" == controls ]]; then
  "$root/data/runtime/eval-venv/bin/python" -u full20/controls.py
else
  "$root/data/runtime/eval-venv/bin/python" -u full20/score_rows.py --owner remote --shards 4 --shard "$1" --workers 6 --idle-exit-seconds 600
fi
