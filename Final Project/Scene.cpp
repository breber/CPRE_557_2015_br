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
, ground(GLPlane3D(0.0, 0.0, 0.0, 500.0, 500.0), GLAppearance("final_project.vs", "single_texture.fs"))
, needsUpdate(true)
{
}

void Scene::drawScene()
{
    ground.first.draw();
}

void Scene::initializeGround(const glm::vec3& groundColor)
{
    // Add the lights
    addLightsToAppearance(ground.second);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = groundColor;
    material._ambient_material = groundColor;
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    ground.second.setMaterial(material);

    // Add a texture for the background display
    GLTexture* grassTexture = new GLTexture();
    grassTexture->loadAndCreateTexture("grass.bmp");
    ground.second.setTexture(grassTexture);

    // Finalize the appearance object
    ground.second.finalize();

    // create the background plane
    ground.first.setApperance(ground.second);
    ground.first.init();

    // If you want to change appearance parameters after you init the object, call the update function
    ground.second.updateLightSources();
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
