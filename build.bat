@echo off
setlocal enabledelayedexpansion

REM ==========================================================
REM  build.bat
REM  Bas is file par DOUBLE-CLICK karein. Baaqi sab kuch
REM  ye script khud sambhal legi:
REM    - agar g++ nahi mila to khud install kar degi
REM    - PATH khud refresh kar degi (naya window kholne ki
REM      zaroorat nahi)
REM    - Main folder aur har Functions\<FunctionName> folder
REM      se saari .cpp files khud dhoond legi
REM    - phir khud compile kar ke program run kar degi
REM ==========================================================

REM --- Is script ki apni location par jaayein ---
cd /d "%~dp0"

REM --- Check karein g++ maujood hai ya nahi ---
where g++ >nul 2>nul
if %errorlevel% equ 0 goto :build

echo.
echo [!] g++ compiler nahi mila. Auto-installing MinGW-w64...
echo     (Ye 1-2 minute le sakta hai, internet par depend karta hai)
echo.

powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0install_compiler.ps1"

echo.
echo [*] Installer khatam hui. PATH refresh kar rahe hain...

for /f "usebackq tokens=*" %%P in (`powershell -NoProfile -Command "[System.Environment]::GetEnvironmentVariable('Path','User')"`) do set "REFRESHED_USER_PATH=%%P"
for /f "usebackq tokens=*" %%P in (`powershell -NoProfile -Command "[System.Environment]::GetEnvironmentVariable('Path','Machine')"`) do set "REFRESHED_MACHINE_PATH=%%P"

set "PATH=%REFRESHED_MACHINE_PATH%;%REFRESHED_USER_PATH%"

where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo.
    echo [FAILED] g++ ab bhi nahi mil raha.
    echo Please ek dafa apna computer RESTART karein aur build.bat
    echo ko dobara chalayein.
    echo.
    pause
    exit /b 1
)

echo [OK] g++ mil gaya:
where g++
echo.

:build
echo Collecting source files...

REM --- Main folder se .cpp files ---
set "SOURCES="
for /r "%~dp0Main" %%f in (*.cpp) do set "SOURCES=!SOURCES! "%%f""

REM --- Har Functions\<FunctionName> folder se .cpp files ---
for /r "%~dp0Functions" %%f in (*.cpp) do set "SOURCES=!SOURCES! "%%f""

if "!SOURCES!"=="" (
    echo.
    echo [FAILED] Koi .cpp file nahi mili. Kya "Main" aur "Functions"
    echo folders isi jagah maujood hain jahan build.bat hai?
    echo.
    pause
    exit /b 1
)

echo Compiling The Developer's Toolkit...
echo.

g++ -std=c++17 -Wall !SOURCES! -o DevelopersToolkit.exe

if %errorlevel% neq 0 (
    echo.
    echo Build FAILED. Please check the errors above.
    pause
    exit /b 1
)

echo.
echo Build successful. Starting the program...
echo.

REM --- Switch the console to UTF-8 so the emojis in the program display
REM     correctly. This does NOT change any program code. ---
chcp 65001 >nul

DevelopersToolkit.exe

echo.
pause
