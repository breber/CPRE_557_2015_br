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
{
}

Garage::~Garage()
{
    // Delete the actual objects to free up some memory
    // This requires other scenes to create their necessary vehicles
    for(std::vector<Vehicle>::iterator vehicleIter = vehicles.begin();
        vehicleIter != vehicles.end();
        ++vehicleIter)
    {
        delete (*vehicleIter).object;
    }
}

void Garage::init()
{
    initializeLights();

    // http://tf3dm.com/3d-model/ford-f-150-raptor-34912.html
    createCar("vehicles/f150.obj", 1.2f);
    // http://tf3dm.com/3d-model/police-car-46912.html
    createCar("vehicles/police.obj", 0.045f);
    // http://tf3dm.com/3d-model/aston-martin-vantage-12213.html
    createCar("vehicles/aston_martin.obj", 0.2f);

    initializeGround(glm::vec3(0.5, 0.51, 0.47));
}

void Garage::initializeLights()
{
    // The GLAppearance takes the address of the light source, so we can't use
    // stack variables to create light sources
    GLDirectLightSource* light_source_ptr = new GLDirectLightSource();
    GLDirectLightSource& light_source = *light_source_ptr;
    light_source._lightPos = glm::vec4(0.0, 20.0, 20.0, 0.0);
    light_source._ambient_intensity = 0.01;
    light_source._specular_intensity = 4.5;
    light_source._diffuse_intensity = 0.5;
    light_source._attenuation_coeff = 0.0;

    lights.push_back(light_source_ptr);

    selectedVehicleHightlight = new GLSpotLightSource();
    GLSpotLightSource& spotlight_source = *selectedVehicleHightlight;
    spotlight_source._lightPos = glm::vec4(13.0, 3.0, 5.0, 1.0);
    spotlight_source._ambient_intensity = 0.0;
    spotlight_source._specular_intensity = 5.0;
    spotlight_source._diffuse_intensity = 8.0;
    spotlight_source._attenuation_coeff = 0.0002;
    spotlight_source._cone_direction = glm::vec3(0.0, 0.0, -1.0);
    spotlight_source._cone_angle = 20.0;

    lights.push_back(selectedVehicleHightlight);
}

void Garage::createCar(const std::string& objPath, float scale)
{
    Vehicle vehicle(objPath, scale, "final_project.vs", "single_texture.fs");

    // Add the lights to the car
    addLightsToAppearance(vehicle.appearance);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
    material._ambient_material = glm::vec3(0.0, 0.0, 1.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    vehicle.appearance.setMaterial(material);

    // Finalize the appearance object
    vehicle.appearance.finalize();

    vehicle.object = new GLObjectObj(objPath);
    vehicle.object->setApperance(vehicle.appearance);
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
    const int vehicleWidth = 35;
    const int countVehicles = vehicles.size();
    int index = 0;
    for(std::vector<Vehicle>::iterator vehicleIter = vehicles.begin();
        vehicleIter != vehicles.end();
        ++vehicleIter, ++index)
    {
        // Rotate the car model 90 degrees so it faces the right direction
        glm::mat4 carMatrix = glm::rotate(static_cast< float >(M_PI / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        // Move it over depending on how many vehicles we have to render
        const float delta = (countVehicles - index - 1) / 2.0 * vehicleWidth;
        carMatrix = carMatrix * glm::translate(glm::vec3(delta, 0.0f, 0.0f));

        // Scale the model by the appropriate value to get them
        // all appropriately the same size
        carMatrix = carMatrix * glm::scale(glm::vec3((*vehicleIter).objScale, (*vehicleIter).objScale, (*vehicleIter).objScale));

        // Update the model matrix with the newly calculated matrix
        (*vehicleIter).object->setMatrix(carMatrix);

        // If it is selected, point the camera at it
        if ((*vehicleIter).object == getSelectedVehicle().object)
        {
            selectedVehicleMatrix = carMatrix;
            selectedDelta = delta;
        }
    }

    // Update the highlight to be over the selected vehicle
    selectedVehicleHightlight->_lightPos = glm::vec4(selectedDelta + 1, 3, 28, 1.0);

    // Add the camera and a camera delta
    const float cameraDelta = (countVehicles - 1) / 4.0 * vehicleWidth;
    glm::mat4 camera_transformation = glm::lookAt(glm::vec3(cameraDelta, 30.0f, 5.0f), glm::vec3(selectedDelta, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // set the view matrix
    SetViewAsMatrix(camera_transformation);

    // Indicate we don't need an update anymore
    needsUpdate = false;
}

void Garage::drawScene()
{
    ground.second.updateLightSources();

    Scene::drawScene();

    // TODO: draw garage scene

    for(std::vector<Vehicle>::iterator vehicleIter = vehicles.begin();
        vehicleIter != vehicles.end();
        ++vehicleIter)
    {
        // Update the lights and draw
        (*vehicleIter).appearance.updateLightSources();
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

const Vehicle& Garage::getSelectedVehicle() const
{
    return vehicles[selectedVehicleIndex];
}
