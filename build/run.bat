@echo off

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
pause

.\Debug\CraftGL.exe