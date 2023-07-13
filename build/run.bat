@echo off
if "%1" == "-build" (
    cmake --build .
) else ( 

if "%1"=="-re" (
    cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
) 
    
cmake --build .
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo Build succeeded!

.\Debug\CraftGL.exe
)