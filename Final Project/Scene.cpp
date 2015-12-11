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
, ground(GLPlane3D(0.0, 0.0, 0.0, 500.0, 500.0), NULL)
{
}

void Scene::drawScene()
{
    ground.first.draw();
}

void Scene::initializeGround(const glm::vec3& groundColor)
{
    // create an apperance object.
    GLAppearance* groundAppearance = new GLAppearance("final_project.vs", "single_texture.fs");

    // Add the lights
    addLightsToAppearance(*groundAppearance);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = groundColor;
    material._ambient_material = groundColor;
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    groundAppearance->setMaterial(material);

    // Add a texture for the background display
    GLTexture* grassTexture = new GLTexture();
    grassTexture->loadAndCreateTexture("grass.bmp");
    groundAppearance->setTexture(grassTexture);

    // Finalize the appearance object
    groundAppearance->finalize();

    // create the background plane
    ground.first.setApperance(*groundAppearance);
    ground.first.init();

    // If you want to change appearance parameters after you init the object, call the update function
    groundAppearance->updateLightSources();

    ground.second = groundAppearance;
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
