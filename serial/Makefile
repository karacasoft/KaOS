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
LDFLAGS := $(LDFLAGS)
LIBS := $(LIBS) -nostdlib -lk -lgcc

ARCHDIR = arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) $(ARCH_CPPFLAGS)
LDFLAGS := $(LDFLAGS) $(ARCH_LDFLAGS)
LIBS := $(LIBS) $(ARCH_LIBS)

FREEOBJS = \
	$(ARCH_FREEOBJS) \
	serial.o \

HOSTEDOBJS = \
	$(ARCH_HOSTEDOBJS) \

OBJS = \
	$(FREEOBJS) \
	$(HOSTEDOBJS) \

BINARIES = serial.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .c .S

all: $(BINARIES)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

serial.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.c.S:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs:
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp -R $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)