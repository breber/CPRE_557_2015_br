function(FindByName baseName moduleNames headerNames)

    STRING(TOUPPER ${baseName} UP_BASE_NAME)
    STRING(TOLOWER ${baseName} LOW_BASE_NAME)
    SET(LIB_NAMES ${UP_BASE_NAME} ${LOW_BASE_NAME} ${moduleNames})
    #MESSAGE(STATUS ${LIB_NAMES})

    FIND_PATH( ${baseName}_INCLUDE_DIR ${headerNames}
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        DOC "The directory where ${headerNames} resides")
    FIND_LIBRARY( ${baseName}_LIBRARY
        NAMES ${LIB_NAMES}
        PATHS
        /usr/lib64
        /usr/lib
        /usr/local/lib64
        /usr/local/lib
        /sw/lib
        /opt/local/lib
        DOC "The ${baseName} library")

    IF (${baseName}_INCLUDE_DIR)
        SET( ${baseName}_FOUND 1 CACHE STRING "Set to 1 if ${baseName} is found, 0 otherwise")
    ELSE (${baseName}_INCLUDE_DIR)
        SET( ${baseName}_FOUND 0 CACHE STRING "Set to 1 if ${baseName} is found, 0 otherwise")
    ENDIF (${baseName}_INCLUDE_DIR)

    MARK_AS_ADVANCED( ${baseName}_FOUND )

endfunction(FindByName)
