{ pkgs }:
pkgs.stdenv.mkDerivation {
  name = "libc";
  buildDepends = [pkgs.flex pkgs.gmp pkgs.mpfr pkgs.libmpc];
  src = pkgs.fetchurl {
    url = "http://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz";
    md5 = "70c9ccf9fac07f762c24f2df2290784d"; 
  };
  unpackPhase = ''
    tar xzf binutils-2.28.tar.gz && rm binutils-2.28.tar.gz;
  '';
  buildPhase = ''
    $src/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
  '';
}
