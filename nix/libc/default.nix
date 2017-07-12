{ pkgs, target, prefix }:
pkgs.stdenv.mkDerivation {
  name = "libc";
  buildDepends = [pkgs.flex pkgs.gmp pkgs.mpfr pkgs.libmpc pkgs.automake];
  src = pkgs.fetchurl {
    url = "http://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz";
    sha256 = "1krgfxnlgjzwfddxfwr0kna94nqy9va5ig8x8l6q87bnzik7jwfd";
  };
}
