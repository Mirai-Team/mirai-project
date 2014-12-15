cmake_minimum_required(VERSION 2.6)

# Setting up project.
project(MiraiProject)
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Include extern libraries.
include_directories(extlibs/headers)
link_directories(extlibs/libs-mingw-tdm/x86)

# Include public headers.
include_directories(include)

# Generate source files list.
file(
        GLOB_RECURSE
        
        source_files
        
        src/*
        include/*
)


# Setting up library (our project).
add_library(
        MiraiProject
        SHARED
        ${source_files}
)

# Setting up link edition.

target_link_libraries(
	MiraiProject
	
	sfml-system-d
	sfml-window-d
	sfml-graphics-d
	sfml-audio-d
	sfml-network-d
)

