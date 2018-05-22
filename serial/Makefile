DEFAULT_HOST = $(shell ../default-host.sh)
HOST ?= $(DEFAULT_HOST)
HOSTARCH = $(shell ../target-triplet-to-arch.sh $(HOST))

CFLAGS ?= -O2 -g

DESTDIR ?=
PREFIX ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
BOOTDIR ?= $(EXEC_PREFIX)/boot
INCLUDEDIR ?= $(PREFIX)/include

CFLAGS := $(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS := $(CPPFLAGS) -D__is_libc -Iinclude
LDFLAGS := $(LDFLAGS)
LIBS := $(LIBS) -nostdlib -lk -lgcc

ARCHDIR = arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS := $(LIBS) $(KERNEL_ARCH_LIBS)



install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R include/. $(DESTDIR)$(INCLUDEDIR)/.

