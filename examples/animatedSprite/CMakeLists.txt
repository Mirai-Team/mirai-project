set(APP_NAME AnimatedSprite)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/examples/${APP_NAME}/${CMAKE_BUILD_TYPE})

# Generate source files list.
file(GLOB_RECURSE source_files src/*)

# Add link directory for Mirai Project.
# link_directories MUST be called before the target is created.
link_directories(${CMAKE_BINARY_DIR}/bin/lib/${CMAKE_BUILD_TYPE})

# Setting up executable.
add_executable(
        ${APP_NAME}
        ${source_files}
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    SYSTEM ${SFML_INCLUDE_DIR}
    SYSTEM ${Boost_INCLUDE_DIRS}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug") # Link Mirai Project debug.
    target_link_libraries(
        ${APP_NAME}
        MiraiProject-d
        ${SFML_LIBRARIES}
        ${Boost_LIBRARIES}
    )
else() # Link Mirai Project release.
    target_link_libraries(
        ${APP_NAME}
        MiraiProject
        ${SFML_LIBRARIES}
        ${Boost_LIBRARIES}
    )
endif()

file(COPY resources/ DESTINATION ${CMAKE_BINARY_DIR}/bin/examples/${APP_NAME}/${CMAKE_BUILD_TYPE}/resources/)
