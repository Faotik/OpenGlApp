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

                pkgs.wayland
                pkgs.wayland-scanner
                pkgs.libxkbcommon
            ];

            commonNativeBuildInputs = [
                pkgs.clang-tools
                pkgs.clang
                pkgs.pkg-config
                pkgs.cmake
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
