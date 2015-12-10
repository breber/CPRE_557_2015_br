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
#include "Plane3D.h"

// stdlib
#include <string>

class Outside : public Scene
{
public:
    Outside(GLObjectObj* selectedVehicle);
    ~Outside() {};

    virtual void updateCamera();
    virtual void drawScene();
    virtual void onKey(int key, int scancode, int action, int mods);
private:
    void initializeGround();

    glm::mat4 vehicleMatrix;
    GLObjectObj* vehicle;

    GLPlane3D ground;
};
