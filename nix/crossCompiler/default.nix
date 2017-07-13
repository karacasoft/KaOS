{ pkgs, target, prefix }:
let
  gcc = import ./gcc.nix {
    binutils = import ./binutils.nix { inherit pkgs; };
    inherit pkgs target prefix;
  };
in
  gcc
