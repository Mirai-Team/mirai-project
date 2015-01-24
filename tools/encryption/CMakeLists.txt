cmake_minimum_required(VERSION 2.6)
project(EncryptionTool)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(APP_NAME EncryptionTool-d)
else()
	set(APP_NAME EncryptionTool)
endif()

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# Generate source files list.
file(
        GLOB_RECURSE
        
        source_files
        
        src/*
)

# Add flags for g++
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-pedantic -pedantic-errors -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wundef -Wlogical-op -Winline -Weffc++ -std=c++11" CACHE STRING "Flags used by the compiler during all build types." FORCE)

    set(CMAKE_CXX_FLAGS_DEBUG "-g" CACHE STRING "Flags used by the compiler during debug builds." FORCE)

    set(CMAKE_CXX_FLAGS_MINSIZEREL "-s -Os" CACHE STRING "Flags used by the compiler during release builds for minimum size" FORCE)

    set(CMAKE_CXX_FLAGS_RELEASE "-s -O2" CACHE STRING "Flags used by the compiler during release builds." FORCE)
endif()

# Setting up executable.
add_executable(
        ${APP_NAME}
        ${source_files}
)

# Detect and add Boost
find_package(Boost 1.54.0 REQUIRED filesystem system thread)
if(Boost_FOUND)
	# The parameter SYSTEM is to treat headers found there as system headers, and 
	# suppress warnings originating from there by using the -isystem flag instead 
	# of the -I flag while building with gcc/g++.
	include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
	
	# Setting up link edition.
    target_link_libraries( 
        ${APP_NAME}
        ${Boost_LIBRARIES}
    )
endif()
