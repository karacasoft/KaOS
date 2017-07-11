FROM centos

# Install: packages
RUN yum -y update
RUN yum -y install git curl gcc make bash python autoconf automake bison flex which \
                   gmp mpfr libmpc-devel bzip2 gcc-c++

# Install: xorriso
WORKDIR $HOME/src

RUN curl -O http://ftp.tu-chemnitz.de/pub/linux/dag/redhat/el7/en/x86_64/rpmforge/RPMS/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm
RUN rpm -Uvh rpmforge-release*rpm
RUN yum -y install xorriso

# Install: grub
RUN git clone git://git.savannah.gnu.org/grub.git
WORKDIR grub
RUN ./autogen.sh
RUN ./configure
RUN make && make install

# Install: Cross compiler
ENV PREFIX=$HOME/opt/cross
ENV TARGET=i686-elf
ENV PATH=$PREFIX/bin:$PATH

## Install: Binutils
WORKDIR $HOME/src
RUN curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz
RUN tar xzvf binutils-2.28.tar.gz && rm binutils-2.28.tar.gz
RUN mkdir build-binutils
WORKDIR build-binutils
RUN ../binutils-2.28/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
RUN make
RUN make install

## Install: GCC
WORKDIR $HOME/src
 
RUN which -- $TARGET-as || echo "$TARGET-as is not in the PATH"

RUN curl -s http://gcc.parentingamerica.com/releases/gcc-5.4.0/gcc-5.4.0.tar.gz > gcc-5.4.0.tar.gz
RUN ls
RUN tar xzvf gcc-5.4.0.tar.gz > /dev/null && rm gcc-5.4.0.tar.gz
RUN mkdir build-gcc
WORKDIR build-gcc
RUN ../gcc-5.4.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers > /dev/null
RUN make all-gcc
RUN make all-target-libgcc
RUN make install-gcc
RUN make install-target-libgcc

# Install: KaOS
RUN yum -y install xorriso
RUN git clone https://github.com/triforce930/KaOS.git
WORKDIR KaOS
RUN ./build.sh
RUN ./iso.sh
