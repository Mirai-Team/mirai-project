cmake_minimum_required(VERSION 2.6)
project(EncryptedResManagerExample)
 
# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
 
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(APP_NAME EncryptedResManagerExample-d)
else()
        set(APP_NAME EncryptedResManagerExample)
endif()
 
set(EXECUTABLE_OUTPUT_PATH .)
 
# Generate source files list.
file(
        GLOB_RECURSE
       
        source_files
       
        src/*
        include/*
)
 
# Add link directory for Mirai Project.
# link_directories MUST be called before the target is created.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        link_directories(${MIRAI_PROJECT_LIB_DIR_DEBUG})
else()
        link_directories(${MIRAI_PROJECT_LIB_DIR_RELEASE})
endif()
 
# Setting up executable.
add_executable(
        ${APP_NAME}
        ${source_files}
)
 
# Set the path where cmake should look for modules.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
 
# Detect and add SFML
# Find any version 2.X of SFML
find_package(SFML 2.0 REQUIRED system window graphics)
if(SFML_FOUND)
        include_directories(SYSTEM ${SFML_INCLUDE_DIR})
       
        # Setting up link edition.
        target_link_libraries(
                ${APP_NAME}
                ${SFML_LIBRARIES}
        )
endif()
 
# Add MiraiProject
include_directories(${MIRAI_PROJECT_INCLUDE_DIR})
 
if(CMAKE_BUILD_TYPE STREQUAL "Debug") # Link Mirai Project debug.
        target_link_libraries(
                ${APP_NAME}
                MiraiProject-d
        )
else() # Link Mirai Project release.
        target_link_libraries(
                ${APP_NAME}
                MiraiProject
        )
endif()
 
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
