@echo off
chcp 65001 > nul
echo ==============================
echo  Building OOP NhanVat - VuKhi
echo ==============================

g++ -std=c++17 -O2 -Wall -Wextra ^
    main.cpp ^
    -o run.exe

if %errorlevel% neq 0 (
    echo.
    echo Build FAILED!
    pause
    exit /b %errorlevel%
)

echo.
echo ===== Build SUCCESS =====
echo Running program...
echo.

run.exe

echo.
echo Program finished.
pause
