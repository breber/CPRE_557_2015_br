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

// course files
#include "GLObjectObj.h"

// stdlib
#include <string>

class Outside : public Scene
{
public:
    Outside(GLObjectObj* selectedVehicle);
    ~Outside() {};

    virtual void init();
    virtual void updateCamera();
    virtual void drawScene();
    virtual void onKey(int key, int scancode, int action, int mods);
private:
    virtual void initializeLights();

    glm::mat4 vehicleMatrix;
    GLObjectObj* vehicle;
};
