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

// stdlib
#include <string>

class Garage : public Scene
{
public:
    Garage();
    ~Garage() {};

    virtual void updateCamera();
    virtual void drawScene();
    virtual void onKey(int key, int scancode, int action, int mods);

    GLObjectObj* getSelectedVehicle() const;
private:
    void createCar(const std::string& objPath);

    std::vector<GLObjectObj*> vehicles;
};
