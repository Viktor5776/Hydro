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
vcpkg.exe install sdl2 --triplet x64-windows
vcpkg.exe install imgui --triplet x64-windows
vcpkg.exe install glm --triplet x64-windows


cd ../../

call vendor\premake\premake5.exe vs2022
PAUSE