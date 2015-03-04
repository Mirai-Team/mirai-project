project(MiraiProject)

cmake_minimum_required(VERSION 2.8.9)

# Setup version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 2)
set(VERSION_PATCH 0)

set(CORE MiraiProject)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# Disable possibility to write binary in sources directory.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Enable release mode by default
if( NOT CMAKE_BUILD_TYPE )
    set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

# Set default build options.
include(cmake/options.cmake)

include(cmake/config.cmake)

# Find any version 2.X of SFML
find_package(SFML 2.0 REQUIRED system window graphics audio network)

# Find any 1.54.X or higher version of Boost.
find_package(Boost 1.54.0 REQUIRED filesystem system thread)

if(MIRAI_WITH_GIT)
    find_package(Git)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    include(cmake/macros/gcc-settings.cmake)
elseif(CMAKE_CXX_COMPILER MATCHES "clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    include(cmake/macros/clang-settings.cmake)
endif()

include(cmake/genrev.cmake)

message("")

message("* MiraiProject           : ${revHash} ${revDate} (${revBranch} branch)")
message("* MiraiProject buildtype : ${CMAKE_BUILD_TYPE}")

if(MIRAI_WITH_GIT)
    message("* Use GIT revision hash  : Yes (default)")
else()
    message("* Use GIT revision hash  : No")
endif()

if(MIRAI_WITH_WARNINGS)
    message("* Show all warnings      : Yes (default)")
else()
    message("* Show all warnings      : No")
endif()

if(MIRAI_SHARED)
    message("* Build shared library   : Yes (default)")
else()
    message("* Build shared library   : No")
endif()

if(MIRAI_EXAMPLES)
    message("* Build examples         : Yes")
else()
    message("* Build examples         : No  (default)")
endif()

if(MIRAI_TOOLS)
    message("* Build tools            : Yes")
else()
    message("* Build tools            : No  (default)")
endif()

message("")

# Add subdirectories to the build.
add_subdirectory(src)

if(MIRAI_TOOLS)
    add_subdirectory(tools)
endif()

if(MIRAI_EXAMPLES)
    add_subdirectory(examples)
endif()
