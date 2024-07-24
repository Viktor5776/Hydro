REM Build script for testbed
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .cpp files.
SET cppFilenames=
FOR /R %%f in (*.cpp) do (
    SET cppFilenames=!cppFilenames! %%f
)

echo "Files:" !cppFilenames!

SET assembly=testbed
SET compilerFlags=-Wall -Werror -std=c++23
SET includeFlags=-Isrc -I..\engine\src -I..\engine\third
SET linkerFlags=-lengine -lmsvcrtd
SET defines=-DHIMPORT

IF "%1" == "release" (
    SET compilerFlags=!compilerFlags! -O3
    SET outputPath=..\bin\release
    SET linkerFlags=!linkerFlags! -L..\bin\release
    ECHO "Building release version of !assembly!..."
) ELSE (
    SET compilerFlags=!compilerFlags! -g
    SET outputPath=..\bin\debug
    SET linkerFlags=!linkerFlags! -L..\bin\debug
    SET defines=!defines! -D_DEBUG
    ECHO "Building debug version of !assembly!..."
)

REM Create the output directory if it does not exist
IF NOT EXIST "!outputPath!" (
    mkdir "!outputPath!"
)

clang++ !cppFilenames! !compilerFlags! -o "!outputPath!\%assembly%.exe" !defines! %includeFlags% !linkerFlags!
