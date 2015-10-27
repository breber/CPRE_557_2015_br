# group:
# Brian R., breber@iastate.edu
# Arko B., abasu@iastate.edu
# Sindhusha D., dsindhu@iastate.edu

cmake_minimum_required(VERSION 2.6)

MESSAGE( STATUS ${CMAKE_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake")
set(CLASS_SOURCE_PATH ${CLASS_SOURCE_PATH} "${CMAKE_SOURCE_DIR}/../../HCI-557-CG/gl_common")

foreach(lib hw4_p1.cpp TriTexture.cpp)
    file(GLOB TEMP_SOURCE ${lib})
    LIST(APPEND SOURCE ${TEMP_SOURCE})
endforeach(lib)

# Include files from the class repo
INCLUDE_DIRECTORIES(${CLASS_SOURCE_PATH})

foreach(f camera.cpp GLAppearance.cpp Shaders.cpp GLSphere.cpp GLObject.cpp CoordSystem.cpp controls.cpp Plane3D.cpp HCI557Common.cpp Texture.cpp)
    file(GLOB TEMP_SOURCE ${CLASS_SOURCE_PATH}/${f})
    LIST(APPEND SOURCE ${TEMP_SOURCE})
endforeach(f)

include(CreateProject)
CreateProject("HW4P1" "${SOURCE}")
