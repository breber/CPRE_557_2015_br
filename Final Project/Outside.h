//
//  Outside.h
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

class Outside : public Scene
{
public:
    Outside(const Vehicle& selectedVehicle);
    virtual ~Outside();

    virtual void init();
    virtual void updateCamera();
    virtual void drawScene();
    virtual void onKey(int key, int scancode, int action, int mods);
private:
    virtual void initializeLights();

    glm::mat4 vehicleMatrix;
    Vehicle vehicle;
};
