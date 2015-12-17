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
#include <glm/ext.hpp>

// glfw includes
#include <GLFW/glfw3.h>

// std
#define _USE_MATH_DEFINES // for C++
#include <math.h>

// course
#include "RayIntersectionTest.h"

Outside::Outside(const Vehicle& selectedVehicle)
: Scene()
, vehicleMatrix()
, vehicle(selectedVehicle.objPath, selectedVehicle.objScale, "final_project.vs", "single_texture.fs")
, track()
{
}

Outside::~Outside()
{
    delete vehicle.object;
}

void Outside::init()
{
    initializeLights();

    // Track initialization
    {
        GLAppearance* appearance = new GLAppearance("final_project.vs", "single_texture.fs");
        addLightsToAppearance(*appearance);

        GLMaterial* material_ptr = new GLMaterial();
        GLMaterial& material = *material_ptr;
        material._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
        material._ambient_material = glm::vec3(0.0, 0.0, 1.0);
        material._specular_material = glm::vec3(1.0, 1.0, 1.0);
        material._shininess = 12.0;
        material._transparency = 1.0;

        appearance->setMaterial(material);
        appearance->finalize();

        track = new GLObjectObj("Track&Terrain.obj");
        track->setApperance(vehicle.appearance);
        track->init();

        // For now, move the track down to the vehicle's level
        glm::mat4 trackMatrix = glm::translate(glm::vec3(0.0f, -1117, 0.0f));
        track->setMatrix(trackMatrix);
    }

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

    // Scale down the car to something reasonable
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
        glm::lookAt(glm::vec3(0.0f, 10.0f, -20.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        // rotate 180 degrees to look at the back of the vehicle
        glm::rotate(static_cast< float >(M_PI), glm::vec3(0.0f, 1.0f, 0.0f)) *
        // scale the camera matrix, since the vehicle matrix has been scaled,
        // and the scaling will be inverted by glm::inverse
        glm::scale(glm::vec3(vehicle.objScale, vehicle.objScale, vehicle.objScale)) *
        // follow the vehicle
        glm::inverse(vehicleMatrixResult);

    // set the view matrix
    SetViewAsMatrix(camera_matrix);

    // Indicate we don't need an update anymore
    needsUpdate = false;
}

void Outside::drawScene()
{
    // Draw the track
    track->draw();

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
        needsUpdate = true;
    }
    // Translation (s = backward)
    else if (key == 83 && (action == GLFW_REPEAT || action == GLFW_PRESS)) // key s
    {
        vehicleMatrix = vehicleMatrix * glm::translate(glm::vec3(0.0f, 0.0f, delta));
        needsUpdate = true;
    }
    // Rotation (a = left)
    if (key == 65 && (action == GLFW_REPEAT || action == GLFW_PRESS)) // key a
    {
        vehicleMatrix = vehicleMatrix * glm::rotate(static_cast< float >(M_PI) / 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        needsUpdate = true;
    }
    // Rotation (d = right)
    else if (key == 68 && (action == GLFW_REPEAT || action == GLFW_PRESS)) // key d
    {
        vehicleMatrix = vehicleMatrix * glm::rotate(-static_cast< float >(M_PI) / 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        needsUpdate = true;
    }

    if (needsUpdate)
    {
        glm::vec3 start(vehicleMatrix[3][0], vehicleMatrix[3][1] + 10, vehicleMatrix[3][2]);
        glm::vec3 end(vehicleMatrix[3][0], vehicleMatrix[3][1] - 50, vehicleMatrix[3][2]);
        std::vector<glm::vec3> res;
        RayIntersectionTest::intersect(start, end, *track, res);

        if (!res.empty())
        {
            glm::vec3 position = res[0];

            vehicleMatrixResult = vehicleMatrix;
            vehicleMatrixResult[3][0] = position[0];
            vehicleMatrixResult[3][1] = position[1];
            vehicleMatrixResult[3][2] = position[2];
            vehicle.object->setMatrix(vehicleMatrixResult);
        }
    }
}
