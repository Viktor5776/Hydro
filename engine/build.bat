REM Build script for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .cpp files.
SET cppFilenames=
FOR /R %%f in (*.cpp) do (
    SET cppFilenames=!cppFilenames! %%f
)

echo "Files:" %cppFilenames%

SET assembly=engine
SET compilerFlags=-g -shared -Wvarargs -Wall -Werror -std=c++23
SET includeFlags=-Isrc -I%VULKAN_SDK%/Include -Ithird/SDL/include -Ithird
SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib -Lthird/SDL/lib/x64 -lSDL2main -lSDL2 -lmsvcrtd 
SET defines=-D_DEBUG -DHEXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%%..."
clang++ %cppFilenames% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%
