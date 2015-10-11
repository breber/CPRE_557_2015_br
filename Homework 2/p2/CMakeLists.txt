# author: Brian Reber (breber)

cmake_minimum_required(VERSION 2.6)

MESSAGE( STATUS ${CMAKE_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake")
set(CLASS_SOURCE_PATH ${CLASS_SOURCE_PATH} "${CMAKE_SOURCE_DIR}/../../HCI-557-CG/assignments/02_Programming_and_3D_Modeling")

foreach(lib hw2.cpp)
    file(GLOB TEMP_SOURCE ${lib})
    LIST(APPEND SOURCE ${TEMP_SOURCE})
endforeach(lib)

# Include files from the class repo
INCLUDE_DIRECTORIES(${CLASS_SOURCE_PATH})

foreach(f controls.cpp HCI557Common.cpp)
    file(GLOB TEMP_SOURCE ${CLASS_SOURCE_PATH}/${f})
    LIST(APPEND SOURCE ${TEMP_SOURCE})
endforeach(f)

include(CreateProject)
CreateProject("HW2P2" "${SOURCE}")
