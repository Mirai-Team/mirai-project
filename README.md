![logo](https://avatars2.githubusercontent.com/u/10365256?v=3&s=200) Mirai Project
=============

[![Build Status](https://travis-ci.org/Mirai-Team/mirai-project.svg?branch=master)](https://travis-ci.org/Mirai-Team/mirai-project)

[![Issue Stats](http://www.issuestats.com/github/Mirai-Team/mirai-project/badge/pr?style=flat)](http://www.issuestats.com/github/Mirai-Team/mirai-project) [![Issue Stats](http://www.issuestats.com/github/Mirai-Team/mirai-project/badge/issue?style=flat)](http://www.issuestats.com/github/Mirai-Team/mirai-project)


## Introduction

Mirai Project is a library for games making purposes mainly by using SFML.


## Authors

+ Benoît CORTIER - main developer (benoit.cortier@gmail.com)
+ Jérôme BOULMIER - main developer (jerome.boulmier@outlook.fr)


## Download

You can get the current development version from the git repository [on Github](https://github.com/Mirai-Team/mirai-project).


## Requirements

+ Platform: Linux, Windows or Mac OSX
+ Boost ≥ 1.54.0 (Modules : system, filesystem and thread)
+ SFML ≥ 2.2
+ Compiler which supports c++11 (GCC ≥ 4.8.1 or Clang ≥ 3.3)
+ (Optional) CMake ≥ 2.8.11.2 / 2.8.9 (Windows / Linux)

## Copyright

License: zlib/libpng

Read [license](license.txt) file.


## Compiling

In order to compile Mirai Project, using c++11 is a compulsory.

You should use cmake (see requirements above) in order to get your makefile or favorite IDE project. There is a [CMakeLists](CMakeLists.txt) file for this purpose. If you don't use cmake, you have to setup yourself your makefile, IDE project, etc.

Open a command line prompt and go to Mirai Project directory.

Windows :
``cd /D \path\to\mirai\project\``
Linux :
``$ cd /path/to/mirai/project/``

Then, make a new directory (called "build" for instance) and go into it :
Windows :
```
mkdir build\
cd build\
```
Linux :
```
$ mkdir build/
$ cd build/
```
This step is a compulsory, because our cmake script disable the possibility to write binaries in a directory containing sources (you can also build in a totally different path).

Now you can generate Makefile, Sublime Text / Code::Blocks / Visual Studio IDE project or whatever you want using cmake and the appropriate generator. Of course, you have to install cmake and add the binary in your system path or to use absolute path to the binary.

Windows
``cmake . --build ..\ -G"GENERATOR_YOU_WANT"``
Linux
``$ cmake . --build ../ -G"GENERATOR_YOU_WANT"``

Type "cmake --help" in your command line prompt to see generators availables on your platform.

You can then build Mirai Project library. Open your IDE if you generated an IDE project, use "make" for Unix Makefiles, "mingw32-make" for MinGW Makefiles, etc.

To build examples, you can set variable "MIRAI_EXAMPLES" to 1.
You can do it by modifying your CMakeCache.txt file and rebuilding cmake cache or with the parameter -D"MIRAI_EXAMPLES=1" when you build the cmake cache.
Windows
``cmake . --build ..\ -G"GENERATOR_YOU_WANT" -D"MIRAI_EXAMPLES=1"``
Linux
``$ cmake . --build ../ -G"GENERATOR_YOU_WANT" -D"MIRAI_EXAMPLES=1"``

To build tools provided with the library, this is the variable "MIRAI_TOOLS" which should be set to 1.


## Contribute

Read [NORMS](NORMS.md) file carefully and respect each of them if you want to contribute.

If you add sources files, you should rebuild your cmake cache :
Windows
``cmake . --build ..\``
Linux
``$ cmake . --build ../``
