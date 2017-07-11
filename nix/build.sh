source $stdenv/setup

set -e
SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

#Append cross compiler binary path to PATH variable
export PATH=$PATH:~/opt/cross/bin

export MAKE=${MAKE:-make}
export HOST=${HOST:-$src/i686-elf}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS=''

export SYSROOT="$out/sysroot"
export CC="$CC --sysroot=$SYSROOT"

#
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
	export CC="$CC -isystem=$INCLUDEDIR"
fi

mkdir -p "$SYSROOT"

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
	(cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done

for PROJECT in $PROJECTS; do
	(cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
