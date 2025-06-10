cd vendor
if not exist vcpkg (
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    start /wait cmd /C bootstrap-vcpkg.bat
    
    cd ..
)
cd vcpkg
::Can defenetly be done with prebuildcommands in premake file but can´t figure that out 
::so we do a quick fix here :D MAKE SURE BAT AND SH have same libraries or problems
vcpkg.exe install sdl3 --triplet x64-windows
vcpkg.exe install imgui --triplet x64-windows
vcpkg.exe install glm --triplet x64-windows
vcpkg.exe install gtest --triplet x64-windows
vcpkg.exe install backward-cpp --triplet x64-windows
vcpkg.exe install nlohmann-json --triplet x64-windows
vcpkg.exe install entt --triplet x64-windows

cd ../../

call vendor\premake\premake5.exe vs2022
PAUSE