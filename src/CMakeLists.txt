file(GLOB_RECURSE sources_animations ${CMAKE_CURRENT_SOURCE_DIR}/animations/* ${CMAKE_SOURCE_DIR}/include/animations/*)

file(GLOB_RECURSE sources_encryption ${CMAKE_CURRENT_SOURCE_DIR}/encryption/* ${CMAKE_SOURCE_DIR}/include/encryption/*)

file(GLOB_RECURSE sources_inputManager ${CMAKE_CURRENT_SOURCE_DIR}/inputManager/* ${CMAKE_SOURCE_DIR}/include/inputManager/*)

file(GLOB_RECURSE sources_parser ${CMAKE_CURRENT_SOURCE_DIR}/parser/* ${CMAKE_SOURCE_DIR}/include/parser/*)

file(GLOB_RECURSE sources_resourcesManagers ${CMAKE_CURRENT_SOURCE_DIR}/resourcesManagers/* ${CMAKE_SOURCE_DIR}/include/resourcesManagers/*)

file(GLOB_RECURSE sources_stat ${CMAKE_CURRENT_SOURCE_DIR}/stat/* ${CMAKE_SOURCE_DIR}/include/stat/*)

file(GLOB_RECURSE sources_updateSystem ${CMAKE_CURRENT_SOURCE_DIR}/updateSystem/* ${CMAKE_SOURCE_DIR}/include/updateSystem/*)

file(GLOB_RECURSE sources_util ${CMAKE_CURRENT_SOURCE_DIR}/util/* ${CMAKE_SOURCE_DIR}/include/util/*)

set(core_sources
    ${sources_animations}
    ${sources_encryption}
    ${sources_inputManager}
    ${sources_parser}
    ${sources_resourcesManagers}
    ${sources_stat}
    ${sources_updateSystem}
    ${sources_util}
)

#
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    SYSTEM ${SFML_INCLUDE_DIR}
    SYSTEM ${Boost_INCLUDE_DIRS}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CORE_NAME MiraiProject-d)
else()
    set(CORE_NAME MiraiProject)
endif()

#set output path
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/lib/${CMAKE_BUILD_TYPE})

#Create MiraiProject lib.
add_library(
    ${CORE_NAME}
    SHARED
    ${core_sources}
)

#Link dependance.
target_link_libraries(
    ${CORE_NAME}
    ${SFML_LIBRARIES}
    ${Boost_LIBRARIES}
)