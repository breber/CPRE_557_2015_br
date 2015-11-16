function(SetupLibraries)

    IF(APPLE)
        INCLUDE_DIRECTORIES(/System/Library/Frameworks)
        FIND_LIBRARY(COCOA_LIBRARY Cocoa)
        FIND_LIBRARY(CV_LIBRARY CoreVideo)
        FIND_LIBRARY(IO_LIBRARY IOKit)
        SET(EXTRA_LIBS ${COCOA_LIBRARY} ${CV_LIBRARY} ${IO_LIBRARY} PARENT_SCOPE)
    ENDIF(APPLE)

    IF(WINDOWS)
        set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../HCI-557-CG/SDK/cmake/")
    ENDIF(WINDOWS)

    # Linux
    # -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread

    foreach(lib GLEW GLM GLFW3 OpenGL)
        FIND_PACKAGE(${lib} REQUIRED)
        STRING(TOUPPER ${lib} LIB_NAME)
        MESSAGE(STATUS "Finding: " ${LIB_NAME})
        MESSAGE(STATUS "  Include: " ${${LIB_NAME}_INCLUDE_DIR})
        MESSAGE(STATUS "  Library: " ${${LIB_NAME}_LIBRARY})
        MESSAGE(STATUS "")

        INCLUDE_DIRECTORIES(${${LIB_NAME}_INCLUDE_DIR})
        if(NOT "${${LIB_NAME}_LIBRARY}" STREQUAL ${LIB_NAME}_LIBRARY-NOTFOUND)
            LIST(APPEND ALL_LIBS ${${LIB_NAME}_LIBRARY})
        endif()
    endforeach(lib)

    SET(ALL_LIBS ${ALL_LIBS} PARENT_SCOPE)

endfunction(SetupLibraries)
