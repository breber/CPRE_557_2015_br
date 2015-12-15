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

// std
#define _USE_MATH_DEFINES // for C++
#include <math.h>

Outside::Outside(const Vehicle& selectedVehicle)
: Scene()
, vehicleMatrix()
, vehicle(selectedVehicle.objPath, selectedVehicle.objScale, "final_project.vs", "single_texture.fs")
{
}

Outside::~Outside()
{
    delete vehicle.object;
}

void Outside::init()
{
    initializeLights();

    // Add the lights to the car
    addLightsToAppearance(vehicle.appearance);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = glm::vec3(0.0, 1.0, 0.0);
    material._ambient_material = glm::vec3(0.0, 1.0, 0.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    vehicle.appearance.setMaterial(material);

    // Finalize the appearance object
    vehicle.appearance.finalize();

    vehicle.object = new GLObjectObj(vehicle.objPath);
    vehicle.object->setApperance(vehicle.appearance);
    vehicle.object->init();

    // Rotate the car model 90 degrees so it faces the right direction
    vehicleMatrix = glm::rotate(static_cast< float >(M_PI / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    vehicleMatrix = vehicleMatrix * glm::scale(glm::vec3(vehicle.objScale, vehicle.objScale, vehicle.objScale));
    vehicle.object->setMatrix(vehicleMatrix);

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
    if (!needsUpdate)
    {
        return;
    }

    // Add the camera and a camera delta
    glm::mat4 camera_matrix =
        // Look at the vehicle
        glm::lookAt(glm::vec3(0.0f, 10.0f, -20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        // rotate 180 degrees to look at the back of the vehicle
        glm::rotate(static_cast< float >(M_PI), glm::vec3(0.0f, 1.0f, 0.0f)) *
        // scale the camera matrix, since the vehicle matrix has been scaled,
        // and the scaling will be inverted by glm::inverse
        glm::scale(glm::vec3(vehicle.objScale, vehicle.objScale, vehicle.objScale)) *
        // follow the vehicle
        glm::inverse(vehicleMatrix);

    // set the view matrix
    SetViewAsMatrix(camera_matrix);

    // Indicate we don't need an update anymore
    needsUpdate = false;
}

void Outside::drawScene()
{
    Scene::drawScene();

    // TODO: draw race track scene

    // Draw the vehicle
    vehicle.object->draw();
}

void Outside::onKey(int key, int scancode, int action, int mods)
{
    const float delta = 1.0f;

    // Translation (w = forward)
    if (key == 87 && (action == GLFW_REPEAT || action == GLFW_PRESS)) // key w
    {
        vehicleMatrix = vehicleMatrix * glm::translate(glm::vec3(0.0f, 0.0f, -delta));
        vehicle.object->setMatrix(vehicleMatrix);
        needsUpdate = true;
    }
    // Translation (s = backward)
    else if (key == 83 && (action == GLFW_REPEAT || action == GLFW_PRESS)) // key s
    {
        vehicleMatrix = vehicleMatrix * glm::translate(glm::vec3(0.0f, 0.0f, delta));
        vehicle.object->setMatrix(vehicleMatrix);
        needsUpdate = true;
    }
}
