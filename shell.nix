with import <nixpkgs> {};
mkShell {
  name = "openvxtest-env";
  buildInputs = [ (opencv4.override { enableGtk3 = true; }) ];
  nativeBuildInputs = [ ninja cmake pandoc gdb valgrind ];
}
