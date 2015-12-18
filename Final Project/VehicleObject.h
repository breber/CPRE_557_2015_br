//
//  VehicleObject.hpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu
//
#pragma once

// course
#include "GLObjectObj.h"

// glm
#include <glm/gtc/quaternion.hpp>

class VehicleObject : public GLObjectObj
{
public:

    VehicleObject(const std::string& objPath);
    ~VehicleObject();


    /*!
     Set a model matrix to move the object around
     @param matrix - the model matrix for this object.
     */
    void setMatrix(glm::mat4& matrix);

    /**
        Interpolate and return the matrix
    */
    glm::mat4& interpolateMat();

private:
    glm::mat4   _target_matrix;
    glm::mat4   _current_matrix;
    glm::vec3   _target_position;
    glm::vec3   _current_position;

    glm::quat   _current_quat;
    glm::quat   _target_quat;

    bool        _position_initialized;
};
