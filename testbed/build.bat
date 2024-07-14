REM Build script for testbed
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .cpp files.
SET cppFilenames=
FOR /R %%f in (*.cpp) do (
    SET cppFilenames=!cppFilenames! %%f
)

echo "Files:" %cppFilenames%

SET assembly=testbed
SET compilerFlags=-g -std=c++23 -v
REM -Wall -Werror
SET includeFlags=-Isrc -I../engine/src/ -I../engine/third
SET linkerFlags=-L../bin/ -lengine.lib -lmsvcrtd 
SET defines=-D_DEBUG -DHIMPORT

ECHO "Building %assembly%%..."
clang++ %cppFilenames% %compilerFlags% -o ../bin/%assembly%.exe %defines% %includeFlags% %linkerFlags%