//
//  VehicleObject.cpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu
//

#include "VehicleObject.h"

VehicleObject::VehicleObject(const std::string& objPath)
: GLObjectObj(objPath)
{
    _position_initialized = false;
    _target_position  = glm::vec3(0.0, 0.0, 0.0);
}


VehicleObject::~VehicleObject()
{
}

void VehicleObject::setMatrix(glm::mat4& matrix)
{
    // with interpolation, remember the target location that you like to find
    _target_matrix = matrix;
    _target_quat = glm::quat_cast(matrix);
    _target_position[0] = _target_matrix[3][0];
    _target_position[1] = _target_matrix[3][1];
    _target_position[2] = _target_matrix[3][2];

    // Just for initialization. Move your object immediately to the location
    if (!_position_initialized)
    {
        _current_quat = glm::quat_cast(matrix);
        _current_position = _target_position;

        // update the matrix.
        _modelMatrix =  matrix;
        glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
        _position_initialized = true;
    }
}

glm::mat4& VehicleObject::interpolateMat()
{
    // Calculate the distance between the target position and the current position.
    glm::vec3 temp = _target_position - _current_position;
    float distance = sqrt(dot(temp, temp));

    glm::quat temp_quad;
    temp_quad.x = _target_quat.x - _current_quat.x;
    temp_quad.y = _target_quat.y - _current_quat.y;
    temp_quad.z = _target_quat.z - _current_quat.z;
    temp_quad.w = _target_quat.w - _current_quat.w;

    // Calculate the distance between the target angle and the current angle.
    float delta_angle = sqrt( (_target_quat.x - _current_quat.x)*(_target_quat.x - _current_quat.x)  +
                         (_target_quat.y - _current_quat.y)*(_target_quat.y - _current_quat.y)  +
                         (_target_quat.z - _current_quat.z)*(_target_quat.z - _current_quat.z)  +
                        (_target_quat.w - _current_quat.w)*(_target_quat.w - _current_quat.w));

    // If the distance is too large, find the next step
    if (distance > 0.01 || delta_angle > 0.01)
    {
        // Linear interpolation of the position
        _current_position = _current_position + temp *  glm::vec3(0.08);

        // Linear interpolation of the rotation using slerp
        _current_quat = glm::slerp(_current_quat, _target_quat, 0.25f);

        // convert the quaternion to a matrix
        _target_matrix = glm::mat4_cast(_current_quat);

        // write the position back.
        _target_matrix[3][0] = _current_position[0];
        _target_matrix[3][1] = _current_position[1];
        _target_matrix[3][2] = _current_position[2];

        // update the model matrix.
        _modelMatrix = _target_matrix;
        glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
    }

    return _modelMatrix;
}
