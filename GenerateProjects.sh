cd vendor
if [ ! -d "vcpkg" ]; then
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh

    vcpkg install sdl2 --triplet x64-linux
    cd ..
fi

# Export vcpkg path for use in scripts
export VCPKG_PATH="$(pwd)/vcpkg"
cd ..

vendor/premake/premake5 gmake2
