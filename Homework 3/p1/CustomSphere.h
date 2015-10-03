//
//  CustomSphere.h
//  Created by Brian Reber
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
    int _numLightsLocation;
    // The light objects
    std::vector< GLSpotLightSource > _light_sources;
};
