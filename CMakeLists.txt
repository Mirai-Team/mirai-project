cmake_minimum_required(VERSION 2.6)
project(MiraiProject)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(APP_NAME MiraiProject-d)
else()
	set(APP_NAME MiraiProject)
endif()

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

# include public headers.
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
        ${APP_NAME}
        SHARED
        ${source_files}
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# Find any version 2.X of SFML
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	
	# Setting up link edition.
	target_link_libraries(
		${APP_NAME}
		${SFML_LIBRARIES}
	)
endif()
