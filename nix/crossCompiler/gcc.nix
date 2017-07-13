{ binutils, pkgs, target, prefix }:
pkgs.stdenv.mkDerivation {
  name = "gcc";
  nativeBuildInputs = (with pkgs; [flex gmp mpfr libmpc]);
  phases = ["unpackPhase" "patchPhase" "configurePhase" "buildPhase"];
  src = pkgs.fetchurl {
    url = "http://gcc.parentingamerica.com/releases/gcc-5.4.0/gcc-5.4.0.tar.gz";
    sha256 = "0c1hbg6n051vxp8lw7mwflrbzny7lv153k3w7mka1sgjqf09w21p";
  };
  patchPhase = ''
    export extracted=$(pwd)
    mkdir -p $out/build-gcc
    cd $out/build-gcc
  '';
  configurePhase = ''
    $extracted/configure --target=${target} --prefix=$out/opt/cross --disable-nls --enable-languages=c,c++ --without-headers
  '';
  hardeningDisable = [ "format" ]; # https://unix.stackexchange.com/a/367990
  buildPhase = ''
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
  '';
}
