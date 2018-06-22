SYSTEM_HEADER_PROJECTS="libc kernel serial"
PROJECTS="libc kernel"

#Append cross compiler binary path to PATH variable
export CROSS_COMP_BASE=~/opt/cross
export CROSS_CC_PATH=$CROSS_COMP_BASE/bin
export PATH=$PATH:$CROSS_CC_PATH

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g -DKAOS_DEBUG_MODE'
export CPPFLAGS=''

export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

#
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
	export CC="$CC -isystem=$INCLUDEDIR"
fi
