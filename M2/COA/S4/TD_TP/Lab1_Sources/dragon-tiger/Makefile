all:
	@ARCH=$$(uname -m); \
	case "$$ARCH" in \
	    aarch64*|arm64*) TARGET=arm64 ;; \
	    *) TARGET=x86_64 ;; \
	esac; \
	cd src/runtime/posix && (cp -f libruntime-$$TARGET.a libruntime.a 2>/dev/null || true); \
	echo "No need to build dragon-tiger in lab1. It is distributed as a binary executable."

submission:
	@git remote -v > VERSION 2>/dev/null || true
	@git rev-parse HEAD >> VERSION 2>/dev/null || true
	cd ../ && zip dragon-tiger.zip -r dragon-tiger -x \*dtiger\* -x \*.a -x \*.o
	@rm -f VERSION
	@echo "You can now submit ../dragon-tiger.zip"
