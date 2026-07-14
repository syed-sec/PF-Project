#!/bin/bash
# ==========================================================
#  build.sh
#  Optional script for Linux/Mac users who want to compile
#  and test the code outside Windows.
#  NOTE: clearScreen() uses "cls" which is a Windows-only
#  command, so the screen will simply not clear on Linux/Mac.
#  Everything else works the same.
# ==========================================================

cd "$(dirname "$0")"

echo "Collecting source files..."
SOURCES=$(find Main Functions -name "*.cpp")

if [ -z "$SOURCES" ]; then
    echo "Build FAILED: no .cpp files found under Main/ or Functions/."
    exit 1
fi

echo "Compiling The Developer's Toolkit..."
g++ -std=c++17 -Wall $SOURCES -o DevelopersToolkit

if [ $? -ne 0 ]; then
    echo "Build FAILED. Please check the errors above."
    exit 1
fi

echo "Build successful. Starting the program..."
./DevelopersToolkit
