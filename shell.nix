with import <nixpkgs> {};
mkShell {
  name = "openvxtest-env";
  buildInputs = [ (opencv3.override { enableGtk3 = true; }) ];
  nativeBuildInputs = [ gcc9 ninja cmake pandoc ];
}
