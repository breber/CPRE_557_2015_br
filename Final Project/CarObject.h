//
//  CarObject.h
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

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
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

// locals
#include "GLObject.h"
#include "GLSphere.h"
#include "Shaders.h"

#include "HCI557Datatypes.h"

class CarObject : public GLSphere
{
public:

    CarObject(float center_x, float center_y, float center_z, float radius, int rows = 10, int segments = 10 );
    ~CarObject();

    /*!
     Init the geometry object
     */
    void init(void);

    /*!
     Draw the objects
     */
    virtual  void draw(void);

    /*!
     Set a model matrix to move the object around
     @param matrix - the model matrix for this object.
     */
    void setMatrix(glm::mat4& matrix);

protected:
    /*
     Inits the shader program for this object
     */
    virtual void initShader(void);

    /*!
     Interpolation function for the matrix /
     the position of the object
     */
    void interpolateMat(void);

private:
    glm::mat4   _target_matrix;
    glm::mat4   _current_matrix;
    glm::vec3   _target_position;
    glm::vec3   _current_position;

    glm::quat   _current_quat;
    glm::quat   _target_quat;

    bool        _position_initialized;
};
