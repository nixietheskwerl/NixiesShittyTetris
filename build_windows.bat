@echo off
REM Native Windows build script for Nixie's Shitty Tetris
REM Requires: Qt6 development libraries installed on Windows
REM            mingw-w64 or MSVC toolchain

setlocal enabledelayedexpansion

REM Try to find Qt6 installation
if defined Qt6_DIR (
    set QT_PATH=!Qt6_DIR!
) else if exist "C:\Qt\6.11.0\msvc2022_64" (
    set QT_PATH=C:\Qt\6.11.0\msvc2022_64
) else if exist "C:\Qt\6.11.0\mingw_64" (
    set QT_PATH=C:\Qt\6.11.0\mingw_64
) else (
    echo Error: Qt6 not found. Please set Qt6_DIR environment variable or install Qt6.
    exit /b 1
)

echo Building for Windows (native)...
echo Using Qt6 from: !QT_PATH!

REM Set Qt tools
set MOC=!QT_PATH!\bin\moc.exe
set RCC=!QT_PATH!\bin\rcc.exe

REM Compile moc files
echo Generating MOC files...
"!MOC!" engine.h -o engine.moc.cpp
"!MOC!" gamewidget.h -o gamewidget.moc.cpp

REM Compile with MSVC or MinGW
REM For MinGW: use g++
REM For MSVC: use cl.exe

if exist "!QT_PATH!\lib\cmake\Qt6" (
    echo Using Qt6 CMake configuration...
    REM Could use cmake if available, but for now use direct compilation
)

REM Direct compilation with MinGW (assumes Qt6 headers in Qt path)
set CXXFLAGS=-fdiagnostics-color=always -g -fPIC
set INCLUDES=-I!QT_PATH!\include -I!QT_PATH!\include\QtWidgets -I!QT_PATH!\include\QtCore -I!QT_PATH!\include\QtGui
set LIBS=-L!QT_PATH!\lib -lQt6Widgets -lQt6Gui -lQt6Core

echo Compiling source files...
g++ %CXXFLAGS% %INCLUDES% -c main.cpp -o main.o
g++ %CXXFLAGS% %INCLUDES% -c engine.cpp -o engine.o
g++ %CXXFLAGS% %INCLUDES% -c gamewidget.cpp -o gamewidget.o
g++ %CXXFLAGS% %INCLUDES% -c playfield.cpp -o playfield.o
g++ %CXXFLAGS% %INCLUDES% -c tetromino.cpp -o tetromino.o

echo Compiling MOC files...
g++ %CXXFLAGS% %INCLUDES% -c engine.moc.cpp -o engine.moc.o
g++ %CXXFLAGS% %INCLUDES% -c gamewidget.moc.cpp -o gamewidget.moc.o

echo Linking...
g++ %CXXFLAGS% -o tetris.exe main.o engine.o gamewidget.o playfield.o tetromino.o engine.moc.o gamewidget.moc.o %LIBS%

if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

echo Build successful! Binary: tetris.exe
endlocal
