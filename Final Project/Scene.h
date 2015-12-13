//
//  Scene.h
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu
#pragma once

// course files
#include "GLAppearance.h"
#include "Plane3D.h"

class Scene
{
public:
    Scene();
    virtual ~Scene() {};

    virtual void init() = 0;
    virtual void updateCamera() = 0;
    virtual void drawScene();
    virtual void onKey(int key, int scancode, int action, int mods) = 0;

protected:
    virtual void initializeLights() = 0;
    void initializeGround(const glm::vec3& groundColor);
    void addLightsToAppearance(GLAppearance& appearance);

    bool needsUpdate;
    std::vector<GLLightSource*> lights;
    std::pair<GLPlane3D, GLAppearance> ground;
};
