Use c++11 with your compiler.

Set these variables in your CMakeCache.txt file if your're using g++ :

+ CMAKE_CXX_FLAGS:STRING=-pedantic -pedantic-errors -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Wlogical-op -Winline -Weffc++ -std=c++11
+ CMAKE_CXX_FLAGS_DEBUG:STRING=-g
+ CMAKE_CXX_FLAGS_RELEASE:STRING=-s -O2
+ CMAKE_CXX_FLAGS_MINSIZEREL:STRING=-s -Os