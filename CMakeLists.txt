cmake_minimum_required(VERSION 2.6)

# Setting up project name.

project(MiraiProject)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

# Include public headers.

include_directories(include)

# Generate source files list.

file(
        GLOB_RECURSE
        
        source_files
        
        src/*
        include/*
)


# Setting up library.

add_library(
        MiraiProject
        SHARED
        ${source_files}
)


