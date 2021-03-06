//
//  CustomSphere.h
//  Group:
//  Brian R., breber@iastate.edu
//  Shrabya K., shrabya@iastate.edu
//  Andrew M., amaxim@iastate.edu
//  Kyle V., vansicek@iastate.edu 
#pragma once

// stl include
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// locals
#include "GLObject.h"
#include "GLSphere.h"
#include "Shaders.h"

#include "HCI557Datatypes.h"

class CustomSphere : public GLSphere
{
public:
    CustomSphere(
        float center_x,
        float center_y,
        float center_z,
        float radius,
        const std::vector< GLSpotLightSource >& lights,
        const std::string& vertexShader,
        const std::string& fragmentShader,
        const glm::vec3& diffuseColor,
        const glm::vec3& ambientColor,
        const glm::vec3& specularColor,
        int rows = 10,
        int segments = 10 );
    ~CustomSphere();

protected:
    /*
        Inits the shader program for this object
     */
    virtual void initShader();

    std::string _vertexShader;
    std::string _fragmentShader;
    glm::vec3 _diffuseColor;
    glm::vec3 _ambientColor;
    glm::vec3 _specularColor;
    int _numLightsLocation;
    // The light objects
    std::vector< GLSpotLightSource > _light_sources;
};
