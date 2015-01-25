project(MiraiProject)

cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if( NOT CMAKE_BUILD_TYPE )
    set(CMAKE_BUILD_TYPE "Debug")
endif()

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

# set default buildoptions and print them
include(cmake/options.cmake)

find_package(SFML 2.0 REQUIRED system window graphics audio network)
find_package(Boost 1.54.0 REQUIRED filesystem system thread)

if(MIRAI_WITH_GIT)
    find_package(Git)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    include(cmake/macros/gcc-settings.cmake)
endif()

include(cmake/genrev.cmake)

message("")
message("* MiraiProject : ${revHash} ${revDate} (${revBranch} branch)")

if(MIRAI_TOOLS)
    message("* Build tools            : Yes")
else()
    message("* Build tools            : No  (default)")
endif()

if(MIRAI_EXAMPLES)
    message("* Build examples         : Yes")
else()
    message("* Build examples         : No  (default)")
endif()

if(MIRAI_WITH_WARNINGS)
    message("* Show all warnings      : Yes (default)")
else()
    message("* Show all warnings      : No")
endif()

if(MIRAI_WITH_GIT)
    message("* Use GIT revision hash  : Yes (default)")
else()
    message("* Use GIT revision hash  : No")
endif()

message("")

add_subdirectory(src)

if(MIRAI_TOOLS)
    add_subdirectory(tools)
endif()

if(MIRAI_EXAMPLES)
    add_subdirectory(examples)
endif()