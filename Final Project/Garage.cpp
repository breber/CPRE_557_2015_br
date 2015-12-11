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
, selectedVehicleHightlight()
, needsUpdate(true)
{
}

Garage::~Garage()
{
    // TODO: clean up unused objects
}

void Garage::init()
{
    initializeLights();

    // http://tf3dm.com/3d-model/puo-4240-60733.html
    createCar("flea.obj", 1.0f);
    // http://tf3dm.com/3d-model/police-car-46912.html
    createCar("police.obj", 0.02f);

    initializeGround(glm::vec3(0.5, 0.51, 0.47));
}

void Garage::initializeLights()
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

    selectedVehicleHightlight = new GLSpotLightSource();
    GLSpotLightSource& spotlight_source = *selectedVehicleHightlight;
    spotlight_source._lightPos = glm::vec4(13.0, 3.0, 5.0, 1.0);
    spotlight_source._ambient_intensity = 0.0;
    spotlight_source._specular_intensity = 5.0;
    spotlight_source._diffuse_intensity = 8.0;
    spotlight_source._attenuation_coeff = 0.0002;
    spotlight_source._cone_direction = glm::vec3(-1.0, -1.0, -1.0);
    spotlight_source._cone_angle = 20.0;

    lights.push_back(selectedVehicleHightlight);
}

void Garage::createCar(const std::string& objPath, float scale)
{
    Vehicle vehicle;
    vehicle.objPath = objPath;
    vehicle.scale = scale;
    vehicle.appearance = new GLAppearance("final_project.vs", "single_texture.fs");

    // Add the lights to the car
    addLightsToAppearance(*vehicle.appearance);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
    material._ambient_material = glm::vec3(0.0, 0.0, 1.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    vehicle.appearance->setMaterial(material);

    // Add a texture for the background display
    // GLTexture* carTexture = new GLTexture();
    // carTexture->loadAndCreateTexture("grass.bmp");
    // carAppearance->setTexture(carTexture);

    // Finalize the appearance object
    vehicle.appearance->finalize();

    vehicle.object = new GLObjectObj(objPath);
    vehicle.object->setApperance(*vehicle.appearance);
    vehicle.object->init();

    vehicles.push_back(vehicle);
}

void Garage::updateCamera()
{
    if (!needsUpdate)
    {
        return;
    }

    glm::mat4 selectedVehicleMatrix;
    float selectedDelta = 0.0f;

    // Update the view matrices and determine camera position
    const int vehicleWidth = 10;
    const int countVehicles = vehicles.size();
    int index = 0;
    for(std::vector<Vehicle>::iterator vehicleIter = vehicles.begin();
        vehicleIter != vehicles.end();
        ++vehicleIter, ++index)
    {
        // Rotate the car model 90 degrees so it faces the right direction
        glm::mat4 carMatrix = glm::rotate(static_cast< float >(M_PI / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        carMatrix = carMatrix * glm::scale(glm::vec3((*vehicleIter).scale, (*vehicleIter).scale, (*vehicleIter).scale));

        // Move it over depending on how many vehicles we have to render
        const float delta = (countVehicles - index + 1) / 2.0 * vehicleWidth;
        carMatrix = carMatrix * glm::translate(glm::vec3(delta, 0.0f, 0.0f));

        // Update the model matrix with the newly calculated matrix
        (*vehicleIter).object->setMatrix(carMatrix);

        // If it is selected, point the camera at it
        if ((*vehicleIter).object == getSelectedVehicle())
        {
            selectedVehicleMatrix = carMatrix;
            selectedDelta = delta;
        }
    }

    // Update the highlight to be over the selected vehicle
    selectedVehicleHightlight->_lightPos = glm::vec4(selectedDelta + 3, 3.0, 5.0, 1.0);

    // Add the camera and a camera delta
    glm::mat4 camera_transformation = glm::lookAt(glm::vec3(13.0f, 10.0f, 5.0f), glm::vec3(selectedDelta, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // set the view matrix
    SetViewAsMatrix(camera_transformation);

    // Indicate we don't need an update anymore
    needsUpdate = false;
}

void Garage::drawScene()
{
    ground.second->updateLightSources();

    Scene::drawScene();

    // TODO: draw garage scene

    for(std::vector<Vehicle>::iterator vehicleIter = vehicles.begin();
        vehicleIter != vehicles.end();
        ++vehicleIter)
    {
        // Update the lights and draw
        (*vehicleIter).appearance->updateLightSources();
        (*vehicleIter).object->draw();
    }
}

void Garage::onKey(int key, int scancode, int action, int mods)
{
    // Change selection highlight on left or right arrow key
    if (key == 263 && action == GLFW_PRESS)
    {
        if (selectedVehicleIndex > 0)
        {
            needsUpdate = true;
            --selectedVehicleIndex;
        }
    }
    else if (key == 262 && action == GLFW_PRESS)
    {
        if (selectedVehicleIndex < vehicles.size() - 1)
        {
            needsUpdate = true;
            ++selectedVehicleIndex;
        }
    }
}

GLObjectObj* Garage::getSelectedVehicle() const
{
    return vehicles[selectedVehicleIndex].object;
}
