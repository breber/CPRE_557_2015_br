//
//  Scene.h
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

#include "Scene.h"

Scene::Scene()
: lights()
{
    initializeLights();
}

void Scene::initializeLights()
{
    // The GLAppearance takes the address of the light source, so we can't use
    // stack variables to create light sources
    GLDirectLightSource* light_source_ptr = new GLDirectLightSource();
    GLDirectLightSource& light_source = *light_source_ptr;
    light_source._lightPos = glm::vec4(0.0, 20.0, 20.0, 0.0);
    light_source._ambient_intensity = 0.2;
    light_source._specular_intensity = 4.5;
    light_source._diffuse_intensity = 1.0;
    light_source._attenuation_coeff = 0.0;

    lights.push_back(light_source_ptr);

    GLSpotLightSource* spotlight_source_ptr = new GLSpotLightSource();
    GLSpotLightSource& spotlight_source = *spotlight_source_ptr;
    spotlight_source._lightPos = glm::vec4(0.0, 0.0, 50.0, 1.0);
    spotlight_source._ambient_intensity = 0.2;
    spotlight_source._specular_intensity = 30.5;
    spotlight_source._diffuse_intensity = 8.0;
    spotlight_source._attenuation_coeff = 0.0002;
    spotlight_source._cone_direction = glm::vec3(-1.0, -1.0, -1.0);
    spotlight_source._cone_angle = 20.0;

    lights.push_back(spotlight_source_ptr);
}

void Scene::addLightsToAppearance(GLAppearance& appearance)
{
    for(std::vector<GLLightSource*>::const_iterator lightIter = lights.begin();
        lightIter != lights.end();
        ++lightIter)
    {
        appearance.addLightSource(*(*lightIter));
    }
}
