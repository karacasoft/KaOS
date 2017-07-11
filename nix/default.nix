let
  pkgs = import <nixpkgs> {};
in
rec {
  libc = import ./libc {
    prefix = "$HOME/opt/cross";
    target = "i686-elf";
    inherit pkgs
  };
  kaos = pkgs.stdenv.mkDerivation {
    name = "kaos-1.0";
    buildDepends = [pkgs.grub pkgs.xorriso];
    wrapped-libc = libc { prefix = ./libc/opt/cross }
    src = pkgs.fetchgit {
      url = git://github.com/triforce930/KaOS;
      rev = "fbb89de9e2227d7666e17549b70cb3523a91fabd";
      sha256 = "1n2vzs8qv6bzx85sln74raxgh7nnwim00pkznhd3276fshll0cnb";
    };

    builder = ./nixbuild.sh;
  };
}