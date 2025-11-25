@echo off
REM Quick Start script for Centauri Carbon Motion Detector (Windows)
REM Checks environment and builds firmware for ESP32-S3 (default board)

echo.
echo ============================================================
echo Centauri Carbon Motion Detector - Quick Start (Windows)
echo ============================================================
echo.

REM Check if Python is available
python --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: Python not found
    echo.
    echo Please install Python 3.10 or later from:
    echo https://www.python.org/downloads/
    echo.
    echo Make sure to check "Add Python to PATH" during installation.
    echo.
    pause
    exit /b 1
)

echo Checking build environment...
echo.
python tools\check_environment.py
if errorlevel 1 (
    echo.
    echo ============================================================
    echo Environment check failed!
    echo ============================================================
    echo.
    echo You have two options:
    echo.
    echo 1. Fix the issues above (install missing dependencies globally)
    echo.
    echo 2. Use the portable environment (recommended for quick start):
    echo    python tools\setup_local_env.py
    echo    python tools\build_local.py
    echo.
    pause
    exit /b 1
)

echo.
echo ============================================================
echo Building firmware for ESP32-S3 (default board)
echo ============================================================
echo.
echo To build for a different board, run:
echo   python tools\build_and_flash.py --env BOARD_NAME
echo.
echo Available boards:
echo   - esp32-s3-dev           (ESP32-S3 DevKitC-1)
echo   - seeed_xiao_esp32c3-dev (Seeed XIAO ESP32-C3)
echo   - seeed_xiao_esp32s3-dev (Seeed XIAO ESP32-S3)
echo.
pause

python tools\build_and_flash.py

echo.
echo ============================================================
echo Build complete!
echo ============================================================
echo.
pause
