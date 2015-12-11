//
//  Outside.cpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

#include "Outside.h"

// GLM
#include <glm/gtx/transform.hpp>

// glfw includes
#include <GLFW/glfw3.h>

Outside::Outside(GLObjectObj* selectedVehicle)
: Scene()
, vehicleMatrix()
, vehicle(selectedVehicle)
{
    // Rotate the car model 90 degrees so it faces the right direction
    vehicleMatrix = glm::rotate(static_cast< float >(M_PI / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Outside::init()
{
    initializeLights();

    // TODO: reset lighting on vehicle?

    // Call super class
    initializeGround(glm::vec3(0.0, 0.8, 0.0));
}

void Outside::initializeLights()
{
    // The GLAppearance takes the address of the light source, so we can't use
    // stack variables to create light sources
    GLDirectLightSource* light_source_ptr = new GLDirectLightSource();
    GLDirectLightSource& light_source = *light_source_ptr;
    light_source._lightPos = glm::vec4(0.0, 20.0, 20.0, 0.0);
    light_source._ambient_intensity = 0.1;
    light_source._specular_intensity = 4.5;
    light_source._diffuse_intensity = 1.0;
    light_source._attenuation_coeff = 0.0;

    lights.push_back(light_source_ptr);
}

void Outside::updateCamera()
{
    // Add the camera and a camera delta
    glm::mat4 camera_transformation = glm::lookAt(glm::vec3(0.0f, 5.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 camera_matrix = camera_transformation * glm::inverse(vehicleMatrix);

    // set the view matrix
    SetViewAsMatrix(camera_matrix);
}

void Outside::drawScene()
{
    Scene::drawScene();

    // TODO: draw race track scene

    // Draw the vehicle
    vehicle->draw();
}

void Outside::onKey(int key, int scancode, int action, int mods)
{
    const float delta = 1.0f;

    // Translation (w = forward)
    if (key == 87 && (action == GLFW_REPEAT || action == GLFW_PRESS)) // key w
    {
        vehicleMatrix = vehicleMatrix * glm::translate(glm::vec3(0.0f, 0.0f, -delta));
        vehicle->setMatrix(vehicleMatrix);
    }
    // Translation (s = backward)
    else if (key == 83 && (action == GLFW_REPEAT || action == GLFW_PRESS)) // key s
    {
        vehicleMatrix = vehicleMatrix * glm::translate(glm::vec3(0.0f, 0.0f, delta));
        vehicle->setMatrix(vehicleMatrix);
    }
}
