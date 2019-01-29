ifeq ($(shell uname), Darwin)
	APPLE_CCFLAGS=-m64
	APPLE_ASFLAGS=-arch x86_64
endif
TARGET=libgt.a
EXAMPLETARGET=printr
BUILDDIR=bin/
PREFIX=/usr/local/lib/
EXAMPLESRC=examples/printr.c
SOURCES=$(wildcard src/*)
override CFLAGS+=-std=c11 -O2 -Wno-gnu $(APPLE_CCFLAGS)
SHARED=-shared
DEVFLAGS=-Werror -Wall -g -fPIC -DNDEBUG -Wfloat-equal -Wundef -Wwrite-strings -Wuninitialized -pedantic -fsanitize=address -O0

all:
	mkdir -p $(BUILDDIR)
	$(CC) $(SOURCES) -o $(BUILDDIR)$(TARGET) $(CFLAGS) $(SHARED)

dev:
	mkdir -p $(BUILDDIR)
	$(CC) $(SOURCES) -o $(BUILDDIR)$(TARGET) $(CFLAGS) $(DEVFLAGS) $(SHARED)

example: all
	mkdir -p $(BUILDDIR)
	$(CC) $(EXAMPLESRC) -o $(BUILDDIR)$(EXAMPLETARGET) $(CFLAGS) -lgt -L$(BUILDDIR) -Isrc

example_dev: dev
	mkdir -p $(BUILDDIR)
	$(CC) $(EXAMPLESRC) -o $(BUILDDIR)$(EXAMPLETARGET) $(CFLAGS) $(DEVFLAGS) -lgt -L$(BUILDDIR) -Isrc

install: all
	install $(BUILDDIR)$(TARGET) $(PREFIX)$(TARGET)

uninstall:
	rm -rf $(PREFIX)$(TARGET)

clean:
	rm -rf $(BUILDDIR)
