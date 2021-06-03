{
  inputs.nixpkgs.url = "github:nixos/nixpkgs";

  outputs = { self, nixpkgs }:
  let pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in {
    devShell.x86_64-linux = pkgs.mkShell { buildInputs = with pkgs; [
      xorg.libX11.dev
      xorg.libXft
      xorg.libXinerama
      gnumake
      gcc
    ]; };
  };
}
