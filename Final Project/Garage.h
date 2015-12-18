//
//  Garage.h
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu
#pragma once

// local files
#include "Scene.h"
#include "Vehicle.h"

// stdlib
#include <string>
#include <utility>

class Garage : public Scene
{
public:
    Garage();
    virtual ~Garage();

    virtual void init();
    virtual void updateCamera();
    virtual void drawScene();
    virtual void onKey(int key, int scancode, int action, int mods);

    const Vehicle& getSelectedVehicle() const;
private:
    virtual void initializeLights();
    void createCar(const std::string& objPath, float scale, const glm::vec3& vehicleColor);
    void initializeWall(const std::string& texturePath, int activeTexture);

    std::vector< std::pair<GLObject*, GLAppearance*> > walls;
    std::vector<Vehicle> vehicles;
    int selectedVehicleIndex;
    GLSpotLightSource* selectedVehicleHightlight;
};
