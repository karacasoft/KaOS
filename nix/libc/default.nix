{ pkgs, target, prefix }:
pkgs.stdenv.mkDerivation {
  name = "libc";
  buildDepends = [pkgs.flex pkgs.gmp pkgs.mpfr pkgs.libmpc];
  src = pkgs.fetchurl {
    url = "http://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz";
    sha256 = "1n2vzs8qv6bzx85sln74raxgh7nnwim00pkznhd3276fshll0cnb";
  };
  unpackPhase = ''
    tar xzf binutils-2.28.tar.gz && rm binutils-2.28.tar.gz;
  '';
  buildPhase = ''
    $src/configure --target=$target --prefix="$prefix" --with-sysroot --disable-nls --disable-werror
  '';
}
