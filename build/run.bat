@echo off


if "%1"=="-re" (
    cmake ..
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