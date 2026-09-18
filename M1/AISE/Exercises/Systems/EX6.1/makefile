CC       := cc
CFLAGS   ?= -Wall -Wextra -std=c11 -Ilib
LDFLAGS  ?= -Wl,-rpath,'$$ORIGIN/lib'
PREFIX   ?= /usr/local
LIBDIR   := lib
TARGET   := main
LIBNAME  := crypto

LIB_STATIC := $(LIBDIR)/lib$(LIBNAME).a
LIB_SHARED := $(LIBDIR)/lib$(LIBNAME).so
LIB_OBJ    := $(LIBDIR)/$(LIBNAME).o
MAIN_OBJ   := $(TARGET).o

.SUFFIXES:
.PHONY: all static shared install clean uninstall

all: static shared $(TARGET)

$(TARGET): $(MAIN_OBJ) $(LIB_STATIC)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MAIN_OBJ) -L$(LIBDIR) -l$(LIBNAME) -o $@

$(MAIN_OBJ): main.c $(LIBDIR)/$(LIBNAME).h
	$(CC) $(CFLAGS) -c $< -o $@

static: $(LIB_STATIC)

shared: $(LIB_SHARED)

$(LIB_STATIC): $(LIB_OBJ)
	ar rcs $@ $<

$(LIB_SHARED): $(LIB_OBJ)
	$(CC) -shared -o $@ $<

$(LIB_OBJ): $(LIBDIR)/$(LIBNAME).c $(LIBDIR)/$(LIBNAME).h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

install: static shared
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/lib
	cp $(LIBDIR)/$(LIBNAME).h $(PREFIX)/include/
	cp $(LIB_STATIC) $(LIB_SHARED) $(PREFIX)/lib/

uninstall:
	rm -f $(PREFIX)/include/$(LIBNAME).h
	rm -f $(PREFIX)/lib/lib$(LIBNAME).a
	rm -f $(PREFIX)/lib/lib$(LIBNAME).so

clean:
	rm -f $(MAIN_OBJ) $(TARGET) $(LIB_OBJ) $(LIB_STATIC) $(LIB_SHARED)
