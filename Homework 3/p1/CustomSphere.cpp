//
//  CustomSphere.cpp
//
//  Created by Brian Reber

#include "CustomSphere.h"

CustomSphere::CustomSphere(
    float center_x,
    float center_y,
    float center_z,
    float radius,
    const std::vector< GLSpotLightSource >& lights,
    const std::string& vertexShader,
    const std::string& fragmentShader,
    int rows,
    int segments )
    : GLSphere(center_x, center_y, center_z, radius, rows, segments)
    , _vertexShader(vertexShader)
    , _fragmentShader(fragmentShader)
    , _numLightsLocation(0)
    , _light_sources()
{
    // Only allow 8 light sources
    for (int i = 0; i < std::min(8UL, lights.size()); ++i) {
        _light_sources.push_back(lights[i]);
    }

    initShader();
}

CustomSphere::~CustomSphere()
{
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(1, _vaoID);
    glDeleteVertexArrays(1, _vaoIDNormals);
    glDeleteProgram(_program);
    glDeleteProgram(_program_normals);
}

/*
 Inits the shader program for this object
 */
void
CustomSphere::initShader()
{
    _program = LoadAndCreateShaderProgram(_vertexShader, _fragmentShader);

    glUseProgram(_program);

    // Vertex information / names

    glBindAttribLocation(_program, 0, "in_Position");
    glBindAttribLocation(_program, 1, "in_Normal");
    glBindAttribLocation(_program, 2, "in_Color");

    // Define the model view matrix.
    _modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model

    _projectionMatrixLocation = glGetUniformLocation(_program, "projectionMatrixBox"); // Get the location of our projection matrix in the shader
    _viewMatrixLocation = glGetUniformLocation(_program, "viewMatrixBox"); // Get the location of our view matrix in the shader
    _modelMatrixLocation = glGetUniformLocation(_program, "modelMatrixBox"); // Get the location of our model matrix in the shader
    _numLightsLocation = glGetUniformLocation(_program, "numLights"); // Get the location of the number of lights

    glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix()[0][0] ); // Send our projection matrix to the shader
    glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &viewMatrix()[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]); // Send our model matrix to the shader
    glUniform1i(_numLightsLocation, (GLint)_light_sources.size()); // Send the number of lights

    // Material
    _material._diffuse_material = glm::vec3(1.0, 0.5, 0.0);
    _material._ambient_material = glm::vec3(1.0, 0.5, 0.0);
    _material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    _material._shininess = 0.0;

    _material._ambientColorPos = glGetUniformLocation(_program, "ambient_color");
    _material._diffuseColorPos = glGetUniformLocation(_program, "diffuse_color");
    _material._specularColorPos = glGetUniformLocation(_program, "specular_color");
    _material._shininessIdx = glGetUniformLocation(_program, "shininess");

    // Send the material to your shader program
    glUniform3fv(_material._ambientColorPos, 1, &_material._ambient_material[0] );
    glUniform3fv(_material._diffuseColorPos, 1, &_material._diffuse_material[0]);
    glUniform3fv(_material._specularColorPos, 1, &_material._specular_material[0]);
    glUniform1f(_material._shininessIdx, _material._shininess);

    // Light
    // Add all the light sources
    for (int i = 0; i < _light_sources.size(); ++i) {
        GLSpotLightSource& light = _light_sources[i];

        std::stringstream lightStr;
        lightStr << "lights[" << i << "]";

        // Read all the index values from the shader program
        light._ambientIdx = glGetUniformLocation(_program, std::string(lightStr.str() + ".ambient_intensity").c_str());
        light._diffuseIdx = glGetUniformLocation(_program, std::string(lightStr.str() + ".diffuse_intensity").c_str());
        light._specularIdx = glGetUniformLocation(_program, std::string(lightStr.str() + ".specular_intensity").c_str());
        light._attenuation_coeffIdx = glGetUniformLocation(_program, std::string(lightStr.str() + ".attenuationCoefficient").c_str());
        light._lightPosIdx = glGetUniformLocation(_program, std::string(lightStr.str() + ".pos").c_str());
        light._cone_angleIdx = glGetUniformLocation(_program, std::string(lightStr.str() + ".cone_angle").c_str());
        light._cone_directionIdx = glGetUniformLocation(_program, std::string(lightStr.str() + ".cone_direction").c_str());

        // Send the light information to your shader program
        glUniform1f(light._ambientIdx, light._ambient_intensity);
        glUniform1f(light._diffuseIdx, light._diffuse_intensity);
        glUniform1f(light._specularIdx, light._specular_intensity);
        glUniform1f(light._attenuation_coeffIdx, light._attenuation_coeff);
        glUniform4fv(light._lightPosIdx, 1, &light._lightPos[0]);

        glUniform1f(light._cone_angleIdx, light._cone_angle);
        glUniform3fv(light._cone_directionIdx, 1, &light._cone_direction[0]);
    }

    glUseProgram(0);
}
