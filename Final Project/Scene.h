//
//  Scene.h
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu
#pragma once

#include "GLAppearance.h"

class Scene
{
public:
    Scene();
    ~Scene() {};

    virtual void updateCamera() = 0;
    virtual void drawScene() = 0;
    virtual void onKey(int key, int scancode, int action, int mods) = 0;

private:
    void initializeLights();

protected:
    void addLightsToAppearance(GLAppearance& appearance);

    std::vector<GLLightSource *> lights;
};
