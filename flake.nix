    {
    description = "App";

    inputs = {
        nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    };

    outputs = { self, nixpkgs }:
        let
            system = "x86_64-linux";
            pkgs = import nixpkgs {
                inherit system;
            };

            commonBuildInputs = [
                pkgs.libGL

                pkgs.sdl3

                pkgs.wayland
                pkgs.libxkbcommon
            ];

            commonNativeBuildInputs = [
                pkgs.gcc
                pkgs.clang-tools
                pkgs.clang
                pkgs.pkg-config
                pkgs.bear
                pkgs.gnumake
            ];
        in {
            devShells.${system} = {
                default = pkgs.mkShell {
                    packages = commonBuildInputs ++ commonNativeBuildInputs;

                    LD_LIBRARY_PATH = "${pkgs.lib.makeLibraryPath commonBuildInputs}";
                    LIBCLANG_PATH = "${pkgs.libclang.lib}/lib";

                    shellHook = ''
                    '';
                };
            };
        };
    }
