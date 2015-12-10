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
, ground(0.0, 0.0, 0.0, 500.0, 500.0)
{
    // Rotate the car model 90 degrees so it faces the right direction
    vehicleMatrix = glm::rotate(static_cast< float >(M_PI / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    initializeGround();
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
    // TODO: draw race track scene
    ground.draw();

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

void Outside::initializeGround()
{
    // create an apperance object.
    GLAppearance* grassAppearance = new GLAppearance("final_project.vs", "single_texture.fs");

    // Add the lights to the car
    addLightsToAppearance(*grassAppearance);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = glm::vec3(0.0, 0.8, 0.0);
    material._ambient_material = glm::vec3(0.0, 0.8, 0.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    grassAppearance->setMaterial(material);

    // Add a texture for the background display
    GLTexture* grassTexture = new GLTexture();
    grassTexture->loadAndCreateTexture("grass.bmp");
    grassAppearance->setTexture(grassTexture);

    // Finalize the appearance object
    grassAppearance->finalize();

    // create the background plane
    ground.setApperance(*grassAppearance);
    ground.init();

    // If you want to change appearance parameters after you init the object, call the update function
    grassAppearance->updateLightSources();
}
