//
//  final_project_main.cpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// glfw includes
#include <GLFW/glfw3.h>

// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Plane3D.h"

using namespace std;

// The handle to the window object
GLFWwindow* window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;

// this is a helper variable to allow us to change the texture blend model
extern int g_change_texture_blend;

GLObject* car;
glm::mat4 g_transform_car;

void addLights(GLAppearance* appearance)
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

    // add the light to this apperance object
    appearance->addLightSource(light_source);

    GLSpotLightSource* spotlight_source_ptr = new GLSpotLightSource();
    GLSpotLightSource& spotlight_source = *spotlight_source_ptr;
    spotlight_source._lightPos = glm::vec4(0.0, 0.0, 50.0, 1.0);
    spotlight_source._ambient_intensity = 0.2;
    spotlight_source._specular_intensity = 30.5;
    spotlight_source._diffuse_intensity = 8.0;
    spotlight_source._attenuation_coeff = 0.0002;
    spotlight_source._cone_direction = glm::vec3(-1.0, -1.0, -1.0);
    spotlight_source._cone_angle = 20.0;

    appearance->addLightSource(spotlight_source);
}

GLObject* createGround()
{
    // create an apperance object.
    GLAppearance* grassAppearance = new GLAppearance("final_project.vs", "single_texture.fs");
    addLights(grassAppearance);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = glm::vec3(0.0, 0.8, 0.0);
    material._ambient_material = glm::vec3(0.0, 0.8, 0.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    grassAppearance->setMaterial(material);

    // Add a texture for the background display
    GLTexture* grassTexture = new GLTexture();
    grassTexture->loadAndCreateTexture("grass.bmp");
    grassAppearance->setTexture(grassTexture);

    // Finalize the appearance object
    grassAppearance->finalize();

    // create the background plane
    GLPlane3D* groundPlane = new GLPlane3D(0.0, 0.0, 0.0, 500.0, 500.0);
    groundPlane->setApperance(*grassAppearance);
    groundPlane->init();

    // If you want to change appearance parameters after you init the object, call the update function
    grassAppearance->updateLightSources();

    return groundPlane;
}

void createCar()
{
    GLAppearance* carAppearance = new GLAppearance("final_project.vs", "single_texture.fs");
    addLights(carAppearance);

    // Create a material object
    GLMaterial* material_ptr = new GLMaterial();
    GLMaterial& material = *material_ptr;
    material._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
    material._ambient_material = glm::vec3(0.0, 0.0, 1.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 12.0;
    material._transparency = 1.0;

    // Add the material to the apperance object
    carAppearance->setMaterial(material);

    // Add a texture for the background display
    GLTexture* carTexture = new GLTexture();
    carTexture->loadAndCreateTexture("grass.bmp");
    carAppearance->setTexture(carTexture);

    // Finalize the appearance object
    carAppearance->finalize();

    GLObjectObj* carObj = new GLObjectObj("car.obj");
    carObj->setApperance(*carAppearance);
    carObj->init();
    car = carObj;

    // Rotate the car model 90 degrees so it is facing the right way
    g_transform_car = glm::rotate(static_cast< float >( M_PI / 2.0f ), glm::vec3(1.0f, 0.0f, 0.0f));
    car->setMatrix(g_transform_car);
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float delta = 0.4;
    bool move = false;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // Translation (w = forward)
    if( (key == 87 && action == GLFW_REPEAT) || (key == 87 && action == GLFW_PRESS) ) // key w
    {
        g_transform_car = g_transform_car * glm::translate(glm::vec3(0.0f, 0.0f, -delta));
        car->setMatrix(g_transform_car);
        move = true;
    }
    // Translation (s = backward)
    else if((key == 83 && action == GLFW_REPEAT) || (key == 83 && action == GLFW_PRESS)) // key s
    {
        g_transform_car = g_transform_car * glm::translate(glm::vec3(0.0f, 0.0f, delta));
        car->setMatrix(g_transform_car);
        move = true;
    }
    // cout << key << endl;
}

int main(int argc, const char * argv[])
{
    // Init the GLFW Window
    window = initWindow();

    // Init the glew api
    initGlew();

    //// Create some models

    // coordinate system
    CoordSystem cs(40.0);

    GLObject* groundPlane = createGround();

    // Create Car Object
    createCar();

    // Set up our green background color
    static const GLfloat clear_color[] = { 0.53f, 0.81f, 0.98f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);

    //// Blending

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Register our key handler
    glfwSetKeyCallback(window, keyboard_callback);

    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while (!glfwWindowShouldClose(window))
    {
        // Add the camera and a camera delta
        glm::mat4 camera_transformation = glm::lookAt(glm::vec3(0.0f, 5.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 camera_matrix = camera_transformation * glm::inverse(g_transform_car);

        // set the view matrix
        SetViewAsMatrix(camera_matrix);

        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR, 0, clear_color);
        glClearBufferfv(GL_DEPTH, 0, clear_depth);

        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());

        // draw the objects
        cs.draw();
        groundPlane->draw();
        car->draw();

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
