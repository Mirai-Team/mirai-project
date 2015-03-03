file(GLOB_RECURSE sources_animations ${CMAKE_CURRENT_SOURCE_DIR}/animations/* ${CMAKE_SOURCE_DIR}/include/animations/*)
file(GLOB_RECURSE sources_encryption ${CMAKE_CURRENT_SOURCE_DIR}/encryption/* ${CMAKE_SOURCE_DIR}/include/encryption/*)
file(GLOB_RECURSE sources_inputManager ${CMAKE_CURRENT_SOURCE_DIR}/inputManager/* ${CMAKE_SOURCE_DIR}/include/inputManager/*)
file(GLOB_RECURSE sources_parser ${CMAKE_CURRENT_SOURCE_DIR}/parser/* ${CMAKE_SOURCE_DIR}/include/parser/*)
file(GLOB_RECURSE sources_resourcesManagers ${CMAKE_CURRENT_SOURCE_DIR}/resourcesManagers/* ${CMAKE_SOURCE_DIR}/include/resourcesManagers/*)
file(GLOB_RECURSE sources_scene ${CMAKE_CURRENT_SOURCE_DIR}/scene/* ${CMAKE_SOURCE_DIR}/include/scene/*)
file(GLOB_RECURSE sources_stat ${CMAKE_CURRENT_SOURCE_DIR}/stat/* ${CMAKE_SOURCE_DIR}/include/stat/*)
file(GLOB_RECURSE sources_updateSystem ${CMAKE_CURRENT_SOURCE_DIR}/updateSystem/* ${CMAKE_SOURCE_DIR}/include/updateSystem/*)
file(GLOB_RECURSE sources_util ${CMAKE_CURRENT_SOURCE_DIR}/util/* ${CMAKE_SOURCE_DIR}/include/util/*)

set(core_sources
    ${sources_animations}
    ${sources_encryption}
    ${sources_inputManager}
    ${sources_parser}
    ${sources_resourcesManagers}
    ${sources_scene}
    ${sources_stat}
    ${sources_updateSystem}
    ${sources_util}
)

# Include library headers.
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add SFML and Boost.
# The parameter SYSTEM is to treat headers found there as system headers, and 
# suppress warnings originating from there by using the -isystem flag instead 
# of the -I flag while building with gcc/g++.
include_directories(
    SYSTEM ${SFML_INCLUDE_DIR}
    SYSTEM ${Boost_INCLUDE_DIRS}
)

# Set output path
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/lib/${CMAKE_BUILD_TYPE})

# Create MiraiProject library.
add_library(
    ${CORE_NAME}
    SHARED
    ${core_sources}
)

set_target_properties(${CORE_NAME} PROPERTIES DEBUG_POSTFIX -d)

if(OS_LINUX)
    include(${CMAKE_SOURCE_DIR}/cmake/macros/unix.cmake)
elseif(OS_WINDOWS)
    include(${CMAKE_SOURCE_DIR}/cmake/macros/windows.cmake)
endif()

# Link SFML and Boost.
target_link_libraries(
    ${CORE_NAME}
    ${SFML_LIBRARIES}
    ${Boost_LIBRARIES}
)
