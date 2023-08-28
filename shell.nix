{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell {
  name = "Advent of Code 2021";

  buildInputs = with pkgs; [ gdbHostCpuOnly clang-tools ];
}
