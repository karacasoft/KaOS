{ pkgs }:
pkgs.stdenv.mkDerivation {
  name = "binutils";
  buildDepends = [pkgs.automake];
  phases = [unpackPhase buildPhase];
  src = pkgs.fetchurl {
    url = "http://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz";
    sha256 = "1krgfxnlgjzwfddxfwr0kna94nqy9va5ig8x8l6q87bnzik7jwfd";
  };
  buildPhase = ''
    ls $src;
  '';
}
