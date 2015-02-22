set(APP_NAME GUIExample)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/examples/${APP_NAME}/${CMAKE_BUILD_TYPE})

# Generate source files list.
file(GLOB_RECURSE source_files src/*)

# Add link directory for Mirai Project.
# link_directories MUST be called before the target is created.
link_directories(${CMAKE_BINARY_DIR}/bin/lib/${CMAKE_BUILD_TYPE})

# Include Mirai Project headers.
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add SFML and Boost.
# The parameter SYSTEM is to treat headers found there as system headers, and 
# suppress warnings originating from there by using the -isystem flag instead 
# of the -I flag while building with gcc/g++.
include_directories(
    SYSTEM ${SFML_INCLUDE_DIR}
    SYSTEM ${Boost_INCLUDE_DIRS}
)

# Setting up executable.
add_executable(
        ${APP_NAME}
        ${source_files}
)


# Link SFML and Boost.
target_link_libraries(
    ${APP_NAME}
    ${SFML_LIBRARIES}
    ${Boost_LIBRARIES}
)

# Link Mirai Project.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Link Mirai Project debug.
    target_link_libraries(
        ${APP_NAME}
        MiraiProject-d
    )
else()
    # Link Mirai Project release.
    target_link_libraries(
        ${APP_NAME}
        MiraiProject
    )
endif()

file(COPY resources/ DESTINATION ${CMAKE_BINARY_DIR}/bin/examples/${APP_NAME}/${CMAKE_BUILD_TYPE}/resources/)
