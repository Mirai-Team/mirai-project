# ![logo](https://avatars2.githubusercontent.com/u/10365256?v=3&s=200) Mirai Project
=============

## Introduction

Mirai Project is a library for games making purposes mainly by using SFML.


## Authors

+ Benoît CORTIER - main developer (benoit.cortier@gmail.com)
+ Jérôme BOULMIER - main developer (jerome.boulmier@outlook.fr)


## Download

You can get the current development version from the git repository [on Github](https://github.com/Mirai-Team/mirai-project).


## Requirements

+ Platform: Linux, Windows or Mac
+ Boost ≥ 1.54.0 (Modules : system, filesystem and thread)
+ CMake ≥ 2.6 / 3.1.0 (Windows / Linux)
+ Compiler which supports c++11


## Copyright

License: zlib/libpng

Read [license.txt](license.txt) file.


## Compiling

In order to compile Mirai Project, using c++11 is a compulsory.  Make sure to add it in your compiler parameters.

You should use cmake 2.6 and higher to get your makefile or favorite IDE project, there is a [CMakeLists.txt](CMakeLists.txt) file.

If you're using g++, we highly recommend you to set following flags for g++ in your CMakeCache.txt file :

+ CMAKE_CXX_FLAGS:STRING=-pedantic -pedantic-errors -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wundef -Wlogical-op -Winline -Weffc++ -std=c++11
+ CMAKE_CXX_FLAGS_DEBUG:STRING=-g
+ CMAKE_CXX_FLAGS_RELEASE:STRING=-s -O2
+ CMAKE_CXX_FLAGS_MINSIZEREL:STRING=-s -Os

Theses flags optimize the library regarding the build purpose (Debug or Release) and configure compiler to be more strict while checking the code.


## Contribute

Read [NORMS.md](NORMS.md) file carefully and respect each of them if you want to contribute.
