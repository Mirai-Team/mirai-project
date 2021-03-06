if(MIRAI_SHARED)
    set_target_properties(${CORE} PROPERTIES DEBUG_POSTFIX -d)
    set_target_properties(${CORE} PROPERTIES SUFFIX "-${VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    if(CMAKE_COMPILER_IS_GNUCXX)
        set_target_properties(${CORE} PROPERTIES PREFIX "")
        set_target_properties(${CORE} PROPERTIES IMPORT_SUFFIX ".a")
    endif()
else()
    set_target_properties(${CORE} PROPERTIES DEBUG_POSTFIX -s-d)
    set_target_properties(${CORE} PROPERTIES RELEASE_POSTFIX -s)
    set_target_properties(${CORE} PROPERTIES MINSIZEREL_POSTFIX -s)
endif()