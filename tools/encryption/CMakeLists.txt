set(APP_NAME EncryptionTool)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/tools/${APP_NAME}/${CMAKE_BUILD_TYPE})

file(GLOB_RECURSE source_files src/*)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# Setting up executable.
add_executable(
    ${APP_NAME}
    ${source_files}
)

target_link_libraries(
    ${APP_NAME}
    ${Boost_LIBRARIES}
)
