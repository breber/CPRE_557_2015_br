# group:
# Brian R., breber@iastate.edu
# Kyle V., vansicek@iastate.edu
# Shrabya K., shrabya@iastate.edu
#
# Note: to run on windows, you have to ensure that the DLLs are installed or in
#       the same directory as the exe, and the shaders and vehicles directory
#       are also in the same directory as the executable.
#       Maybe we can use cmake's install feature for this...

cmake_minimum_required(VERSION 2.6)

MESSAGE( STATUS ${CMAKE_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake")
set(CLASS_SOURCE_PATH ${CLASS_SOURCE_PATH} "${CMAKE_SOURCE_DIR}/../HCI-557-CG/gl_common")

foreach(lib final_project_main.cpp CustomTexture.cpp Garage.cpp Outside.cpp Scene.cpp Vehicle.cpp)
    file(GLOB TEMP_SOURCE ${lib})
    LIST(APPEND SOURCE ${TEMP_SOURCE})
endforeach(lib)

# Include files from the class repo
INCLUDE_DIRECTORIES(${CLASS_SOURCE_PATH})

foreach(f camera.cpp GLAppearance.cpp Shaders.cpp GLSphere.cpp GLObject.cpp GLObjectObj.cpp CoordSystem.cpp controls.cpp Plane3D.cpp HCI557Common.cpp Texture.cpp RayIntersectionTest.cpp)
    file(GLOB TEMP_SOURCE ${CLASS_SOURCE_PATH}/${f})
    LIST(APPEND SOURCE ${TEMP_SOURCE})
endforeach(f)

include(CreateProject)
CreateProject("FinalProject" "${SOURCE}")
