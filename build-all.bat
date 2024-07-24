@ECHO OFF
REM Build Everything

IF "%1" == "release" (
    ECHO "Building release version of everything..."
) ELSE (
    ECHO "Building debug version of everything..."
)


PUSHD engine
CALL build.bat %1
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

PUSHD testbed
CALL build.bat %1
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "All assemblies built successfully."

ECHO "Copying DLLs to bin directory..."

REM copy dlls to the bin directory if they do not exist

REM chose the correct directory for the current build
IF "%1" == "release" (
    PUSHD bin\release
) ELSE (
    PUSHD bin\debug
)

REM SDL2.dll
IF NOT EXIST SDL2.dll (
    COPY ..\..\engine\third\SDL\lib\x64\SDL2.dll 
)

POPD

ECHO "Build completed."