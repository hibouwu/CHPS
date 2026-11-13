bin_PROGRAMS = dtiger

dtiger_SOURCES = driver.cc
dtiger_CXXFLAGS = -pedantic -Wall $(LLVM_CPPFLAGS) -fexceptions
dtiger_LDADD = ../ast/libast.a ../parser/libparser.a ../irgen/libirgen.a ../utils/libutils.a $(BOOST_PROGRAM_OPTIONS_LIB) $(LLVM_LIBS)
AM_LDFLAGS = $(BOOST_LDFLAGS) $(LLVM_LDFLAGS)
CLEANFILES=

BUILT_SOURCES = arch-sync

.PHONY: arch-sync
arch-sync:
	@ARCH=$$(uname -m); case "$$ARCH" in aarch64*|arm64*) T=arm64;; *) T=x86_64;; esac; \
	if [ -f ../parser/libparser-$$T.a ]; then cmp -s ../parser/libparser-$$T.a ../parser/libparser.a 2>/dev/null || cp -f ../parser/libparser-$$T.a ../parser/libparser.a 2>/dev/null || true; fi; \
	if [ -f ../ast/libast-$$T.a ]; then cmp -s ../ast/libast-$$T.a ../ast/libast.a 2>/dev/null || cp -f ../ast/libast-$$T.a ../ast/libast.a 2>/dev/null || true; fi; \
	if [ -f ../irgen/libirgen-$$T.a ]; then cmp -s ../irgen/libirgen-$$T.a ../irgen/libirgen.a 2>/dev/null || cp -f ../irgen/libirgen-$$T.a ../irgen/libirgen.a 2>/dev/null || true; fi
