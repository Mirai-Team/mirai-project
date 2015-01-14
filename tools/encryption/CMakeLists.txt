cmake_minimum_required(VERSION 2.6)
project(MiraiEncryption)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(APP_NAME EncryptionExample-d)
else()
	set(APP_NAME EncryptionExample)
endif()

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# include public headers.
include_directories(include)

# Generate source files list.
file(
        GLOB_RECURSE
        
        source_files
        
        src/*
        include/*
)

# Setting up executable.
add_executable(
        ${APP_NAME}
        ${source_files}
)

# Detec and add Boost
find_package(Boost 1.54.0 COMPONENTS filesystem system)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	
	# Setting up link edition.
    target_link_libraries( 
        ${APP_NAME}
        ${Boost_LIBRARIES}
    )
endif()
