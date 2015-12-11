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

// local
#include "Garage.h"
#include "Outside.h"

using namespace std;

// The handle to the window object
GLFWwindow* window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;

Scene* currentScene;

Garage* garageScene;
Outside* outsideScene;

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // std::cout << "key: " << key << std::endl;

    // For now, toggle between scenes with 't'
    if (key == 84 && action == GLFW_PRESS) // t
    {
        std::cout << "toggling scene" << std::endl;
        if (currentScene == garageScene)
        {
            if (!outsideScene)
            {
                outsideScene = new Outside(garageScene->getSelectedVehicle());
                outsideScene->init();
            }
            currentScene = outsideScene;
        }
        else
        {
            currentScene = garageScene;
        }

        return;
    }

    if (currentScene)
    {
        currentScene->onKey(key, scancode, action, mods);
    }
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

    garageScene = new Garage();
    garageScene->init();
    currentScene = garageScene;

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
        currentScene->updateCamera();

        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR, 0, clear_color);
        glClearBufferfv(GL_DEPTH, 0, clear_depth);

        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());

        // draw the objects
        cs.draw();
        currentScene->drawScene();

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
