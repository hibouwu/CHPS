#!/usr/bin/env bash
set -euo pipefail
root=/scratch_p/hibouwu/coderujb/full20-eval-aeV81g
cd "$root"
python_bin=/apps/2025/spack_install/linux-rhel9-zen4/linux-rhel9-zen4/gcc-14.2.0/python-3.11.9-2celb2jubj3ho6k56vyf4fonosldjxej/bin/python3
perl_bin=/apps/2025/spack_install/linux-rhel9-zen4/linux-rhel9-zen4/gcc-14.2.0/perl-5.40.0-7cjrbpcgin5xh5wdnw2b7tqbtpnjktlj/bin
export PATH="$perl_bin:$PATH"
export PERL_CPANM_HOME="$root/cpan-work"
"$python_bin" -m venv data/runtime/eval-venv
 data/runtime/eval-venv/bin/python -m pip install --disable-pip-version-check pyarrow==20.0.0 javalang==0.13.0
perl data/runtime/cpanm -L "$root/data/runtime/perl-local" --notest DBI DBD::CSV URI JSON JSON::Parse
export PERL5LIB="$root/data/runtime/perl-local/lib/perl5"
perl -MDBI -MDBD::CSV -MURI -MJSON -MJSON::Parse -e 'print "Perl dependency checks passed\n"'
data/runtime/eval-venv/bin/python -m pip freeze > python-versions.txt
perl -V > perl-version.txt
printf 'bootstrap complete\n'
