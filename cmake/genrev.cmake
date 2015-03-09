set(GIT_EXEC ${GIT_EXECUTABLE})

if(NOT MIRAI_WITH_GIT)
    set(revDate "1970-01-01 00:00:00 +0000")
    set(revHash "unknown")
    set(revBranch "unknown")
else()
    if(GIT_EXEC)
        execute_process(
            COMMAND "${GIT_EXEC}" describe --tags --dirty=+ --abbrev=4
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE revHash
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        execute_process(
            COMMAND "${GIT_EXEC}" show -s --format=%ci
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE revDate
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        execute_process(
            COMMAND "${GIT_EXEC}" rev-parse --abbrev-ref HEAD
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE revBranch
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
    endif()
endif()