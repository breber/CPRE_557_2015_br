cmake_minimum_required(VERSION 2.6)

MESSAGE( STATUS ${CMAKE_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake")

foreach(lib example.cpp)
    file(GLOB TEMP_SOURCE ${lib})
    LIST(APPEND SOURCE ${TEMP_SOURCE})
endforeach(lib)

include(CreateProject)
CreateProject("HW2P1" "${SOURCE}")
