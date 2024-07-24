REM Build script for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .cpp files.
SET cppFilenames=
FOR /R %%f in (*.cpp) do (
    SET cppFilenames=!cppFilenames! %%f
)

echo "Files:" !cppFilenames!

SET assembly=engine
SET compilerFlags=-shared -Wall -Werror -std=c++23
SET includeFlags=-Isrc -I%VULKAN_SDK%\Include -Ithird\SDL\include -Ithird
SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%\Lib -Lthird\SDL\lib\x64 -lSDL2main -lSDL2 -lmsvcrtd 
SET defines=-DHEXPORT -D_CRT_SECURE_NO_WARNINGS

IF "%1" == "release" (
    SET compilerFlags=!compilerFlags! -O3
    SET outputPath=..\bin\release
    ECHO "Building release version of !assembly!... "
) ELSE (
    SET compilerFlags=!compilerFlags! -g
    SET defines=!defines! -D_DEBUG
    SET outputPath=..\bin\debug
    ECHO "Building debug version of !assembly!... "
)

REM Create the output directory if it does not exist
IF NOT EXIST "!outputPath!" (
    mkdir !outputPath!
)

clang++ !cppFilenames! !compilerFlags! -o !outputPath!\%assembly%.dll !defines! %includeFlags% %linkerFlags%
