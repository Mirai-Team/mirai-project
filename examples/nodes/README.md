Simple Window Example
====================

A simple example using nodes with Mirai Project library.

----------

## Requirements

 - Platform: Linux, Windows or Mac
 - SFML ≥ 2.0 (Modules : system, window, graphics)
 - CMake ≥ 2.6 / 3.1.0 (Windows / Linux)
 - Compiler which supports c++11

## Compiling

In order to compile this example, using c++11 is a compulsory.  Make sure to add it in your compiler parameters.

You should use cmake 2.6 and higher to get your makefile or favourite IDE project, there is a [CMakeLists](CMakeLists.txt) file.

If you're using g++, you can set following variables in your CMakeCache.txt file :

- CMAKE_CXX_FLAGS:STRING=-std=c++11
- CMAKE_CXX_FLAGS_DEBUG:STRING=-g
- CMAKE_CXX_FLAGS_RELEASE:STRING=-s -O2
- CMAKE_CXX_FLAGS_MINSIZEREL:STRING=-s -Os

Theses flags optimize the executable regarding the build purpose (Debug or Release) and configure g++ to use c++11.

To use Mirai Project library, the [CMakeLists](CMakeLists.txt) will look after theses variables :

- MIRAI_PROJECT_INCLUDE_DIR:FILEPATH=/path/to/mirai_project/include
- MIRAI_PROJECT_LIB_DIR_DEBUG:FILEPATH=/path/to/mirai_project/lib/Debug
- MIRAI_PROJECT_LIB_DIR_RELEASE:FILEPATH=/path/to/mirai_project/lib/Release

You can simply add them in your CMakeCache.txt file.

## Running the program

To run, the program need access to following libraries : 

- libsndfile-1
- openal32
- sfml-system-2
- sfml-window-2
- sfml-graphics-2
- sfml-audio-2
- libboost_filesystem
- libboost_system
- libMiraiProject

Under Windows it should be "Dynamic Link Library" files (.dll) and under Unix based systems "Shared Objects" files (.so).
Some of them exists as debug library and release library (boost, mirai project and sfml). Put what you need in the build folder except if you installed them somewhere in your system path.


