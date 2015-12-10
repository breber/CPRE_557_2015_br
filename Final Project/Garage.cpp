//
//  Garage.cpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

#include "Garage.h"

// GLM
#include <glm/gtx/transform.hpp>

// glfw includes
#include <GLFW/glfw3.h>

Garage::Garage()
: Scene()
, vehicles()
, selectedVehicleIndex(0)
{
    // Car model from http://tf3dm.com/3d-model/puo-4240-60733.html
    createCar("car.obj");
    createCar("car.obj");
}

void Garage::createCar(const std::string& objPath)
{
    GLAppearance* carAppearance = new GLAppearance("final_project.vs", "single_texture.fs");

    // Add the lights to the car
    addLightsToAppearance(*carAppearance);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
    material._ambient_material = glm::vec3(0.0, 0.0, 1.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    carAppearance->setMaterial(material);

    // Add a texture for the background display
    // GLTexture* carTexture = new GLTexture();
    // carTexture->loadAndCreateTexture("grass.bmp");
    // carAppearance->setTexture(carTexture);

    // Finalize the appearance object
    carAppearance->finalize();

    GLObjectObj* carObj = new GLObjectObj(objPath);
    carObj->setApperance(*carAppearance);
    carObj->init();

    vehicles.push_back(carObj);
}

void Garage::updateCamera()
{
    glm::mat4 selectedVehicleMatrix;

    // Update the view matrices and determine camera position
    const int vehicleWidth = 10;
    const int countVehicles = vehicles.size();
    int index = 0;
    for(std::vector<GLObjectObj *>::iterator vehicleIter = vehicles.begin();
        vehicleIter != vehicles.end();
        ++vehicleIter, ++index)
    {
        // Rotate the car model 90 degrees so it faces the right direction
        glm::mat4 carMatrix = glm::rotate(static_cast< float >(M_PI / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        // Move it over depending on how many vehicles we have to render
        const float delta = (countVehicles - index + 1) / 2.0 * vehicleWidth;
        carMatrix = carMatrix * glm::translate(glm::vec3(delta, 0.0f, 0.0f));

        // Update the model matrix with the newly calculated matrix
        (*vehicleIter)->setMatrix(carMatrix);

        // If it is selected, point the camera at it
        if (*vehicleIter == getSelectedVehicle())
        {
            selectedVehicleMatrix = carMatrix;
        }
    }

    // Add the camera and a camera delta
    glm::mat4 camera_transformation = glm::lookAt(glm::vec3(0.0f, 5.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 camera_matrix = camera_transformation * glm::inverse(selectedVehicleMatrix);

    // set the view matrix
    SetViewAsMatrix(camera_matrix);
}

void Garage::drawScene()
{
    // TODO: draw garage scene

    // Draw each vehicle
    for(std::vector<GLObjectObj *>::iterator vehicleIter = vehicles.begin();
        vehicleIter != vehicles.end();
        ++vehicleIter)
    {
        (*vehicleIter)->draw();
    }
}

void Garage::onKey(int key, int scancode, int action, int mods)
{
    // Change selection highlight on left or right arrow key
    if (key == 263 && action == GLFW_PRESS)
    {
        if (selectedVehicleIndex > 0)
        {
            --selectedVehicleIndex;
        }
    }
    else if (key == 262 && action == GLFW_PRESS)
    {
        if (selectedVehicleIndex < vehicles.size() - 1)
        {
            ++selectedVehicleIndex;
        }
    }
}

GLObjectObj* Garage::getSelectedVehicle() const
{
    return vehicles[selectedVehicleIndex];
}
