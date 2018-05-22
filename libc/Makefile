DEFAULT_HOST = $(shell ../default-host.sh)
HOST ?= $(DEFAULT_HOST)
HOSTARCH = $(shell ../target-triplet-to-arch.sh $(HOST))

CFLAGS ?= -O2 -g

DESTDIR ?=
PREFIX ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
LIBDIR ?= $(EXEC_PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include

CFLAGS := $(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS := $(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS := $(CFLAGS)
LIBK_CPPFLAGS := $(CPPFLAGS) -D__is_libk

ARCHDIR = arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(ARCH_CPFLAGS)
CPPFLAGS := $(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS := $(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS := $(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS = \
	$(ARCH_FREEOBJS) \
	string/strlen.o \
	string/strcpy.o \
	string/strcmp.o \
	string/memset.o \
	string/memcpy.o \
	stdio/printf.o \
	stdio/putchar.o \
	stdio/puts.o \
	stdlib/atoi.o \
	stdlib/itoa.o \

HOSTEDOBJS = \

OBJS = \
	$(FREEOBJS) \
	$(HOSTEDOBJS) \

LIBK_OBJS = $(FREEOBJS:.o=.libk.o)

BINARIES=libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.c.S:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp -R $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
