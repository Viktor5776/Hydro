@ECHO OFF
REM Build Everything

ECHO "Building everything..."


PUSHD engine
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

PUSHD testbed
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "All assemblies built successfully."

ECHO "Copying DLLs to bin directory..."

REM copy dlls to the bin directory if they do not exist
REM SDL2.dll
IF NOT EXIST bin\SDL2.dll (
    COPY engine\third\SDL\lib\x64\SDL2.dll bin\
)