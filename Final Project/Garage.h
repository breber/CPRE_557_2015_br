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

// course files
#include "GLObjectObj.h"
#include "GLSphere.h"

// stdlib
#include <string>
#include <utility>

class Garage : public Scene
{
public:
    Garage();
    ~Garage();

    virtual void init();
    virtual void updateCamera();
    virtual void drawScene();
    virtual void onKey(int key, int scancode, int action, int mods);

    GLObjectObj* getSelectedVehicle() const;
private:
    struct Vehicle
    {
        std::string objPath;
        float scale;
        GLObjectObj* object;
        GLAppearance* appearance;
    };

    virtual void initializeLights();
    void createCar(const std::string& objPath, float scale);

    std::vector<Vehicle> vehicles;
    int selectedVehicleIndex;
    bool needsUpdate;
    GLSpotLightSource* selectedVehicleHightlight;
};
