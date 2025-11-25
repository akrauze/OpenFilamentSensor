#!/bin/bash
# Quick Start script for Centauri Carbon Motion Detector (Linux/Mac)
# Checks environment and builds firmware for ESP32-S3 (default board)

echo ""
echo "============================================================"
echo "Centauri Carbon Motion Detector - Quick Start (Linux/Mac)"
echo "============================================================"
echo ""

# Check if Python 3 is available
if ! command -v python3 &> /dev/null; then
    echo "ERROR: python3 not found"
    echo ""
    echo "Please install Python 3.10 or later:"
    echo "  - Ubuntu/Debian: sudo apt install python3 python3-pip python3-venv"
    echo "  - macOS: brew install python3"
    echo "  - Or download from: https://www.python.org/downloads/"
    echo ""
    exit 1
fi

echo "Checking build environment..."
echo ""
python3 tools/check_environment.py
if [ $? -ne 0 ]; then
    echo ""
    echo "============================================================"
    echo "Environment check failed!"
    echo "============================================================"
    echo ""
    echo "You have two options:"
    echo ""
    echo "1. Fix the issues above (install missing dependencies globally)"
    echo ""
    echo "2. Use the portable environment (recommended for quick start):"
    echo "   python3 tools/setup_local_env.py"
    echo "   python3 tools/build_local.py"
    echo ""
    exit 1
fi

echo ""
echo "============================================================"
echo "Building firmware for ESP32-S3 (default board)"
echo "============================================================"
echo ""
echo "To build for a different board, run:"
echo "  python3 tools/build_and_flash.py --env BOARD_NAME"
echo ""
echo "Available boards:"
echo "  - esp32-s3-dev           (ESP32-S3 DevKitC-1)"
echo "  - seeed_xiao_esp32c3-dev (Seeed XIAO ESP32-C3)"
echo "  - seeed_xiao_esp32s3-dev (Seeed XIAO ESP32-S3)"
echo ""
read -p "Press Enter to continue..."

python3 tools/build_and_flash.py

echo ""
echo "============================================================"
echo "Build complete!"
echo "============================================================"
echo ""
