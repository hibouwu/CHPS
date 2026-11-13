AC_INIT([dragon-tiger], [submission], [])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall subdir-objects foreign])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([config.h])
AC_PROG_BISON([2.7])
AC_PROG_YACC
AC_PROG_LEX
AC_PROG_CXX
AM_PROG_AS
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])
AM_PROG_AR
AC_PROG_RANLIB

AC_REQUIRE_AUX_FILE([tap-driver.sh])

AX_BOOST_BASE([1.48],, [AC_MSG_ERROR([dragon-tiger needs Boost, but it was not found in your system])])
AX_BOOST_PROGRAM_OPTIONS


AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/ast/Makefile
                 src/driver/Makefile
                 src/utils/Makefile
                ])


AC_CANONICAL_HOST
case "$host_cpu" in
  aarch64*|arm64*) TARGET_ARCH=arm64 ;;
  *) TARGET_ARCH=x86_64 ;;
esac
AC_CONFIG_COMMANDS([arch-libs], [
  if test -d src/parser -a -f "src/parser/libparser-$TARGET_ARCH.a"; then
    cp -f "src/parser/libparser-$TARGET_ARCH.a" src/parser/libparser.a 2>/dev/null || true
  fi
  if test -d src/ast -a -f "src/ast/libast-$TARGET_ARCH.a"; then
    cp -f "src/ast/libast-$TARGET_ARCH.a" src/ast/libast.a 2>/dev/null || true
  fi
  if test -d src/irgen -a -f "src/irgen/libirgen-$TARGET_ARCH.a"; then
    cp -f "src/irgen/libirgen-$TARGET_ARCH.a" src/irgen/libirgen.a 2>/dev/null || true
  fi
], [TARGET_ARCH=$TARGET_ARCH])

AC_OUTPUT
