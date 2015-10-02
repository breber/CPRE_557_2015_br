//
//  hw3.cpp
//  Part 1 of HW3
//
//  Created by Brian Reber
//  Copyright (c) 2015 -. All rights reserved.
//

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
#include "CustomSphere.h"

using namespace std;

// The handle to the window object
GLFWwindow* window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;

int main(int argc, const char * argv[])
{
    // Init glfw, create a window, and init glew

    // Init the GLFW Window
    window = initWindow();

    // Init the glew api
    initGlew();

    // Setup our light sources
    std::vector< GLSpotLightSource > lights;
    GLSpotLightSource light_source;

    // First spot light (sharp cutoff angle)
    // TODO: get the right parameters
    light_source._lightPos = glm::vec4(10.0, 20.0, 0.0, 0.0);
    light_source._ambient_intensity = 0.3;
    light_source._specular_intensity = 5.0;
    light_source._diffuse_intensity = 8.0;
    light_source._attenuation_coeff = 0.02;

    light_source._cone_angle = 12.0; // in degree
    light_source._cone_direction = glm::vec3(-1.0, -1.0, 0.0); // this must be aligned with the object and light position.
    lights.push_back(light_source);

    // Add a diffuse light
    // TODO: get the right parameters
    light_source._lightPos = glm::vec4(-10.0, -10.0, 0.0, 1.0);
    light_source._ambient_intensity = 0.3;
    light_source._specular_intensity = 10.0;
    light_source._diffuse_intensity = 4.0;
    light_source._attenuation_coeff = 0.02;

    light_source._cone_angle = 40.0; // in degree
    light_source._cone_direction = glm::vec3(-1.0, -1.0, 0.0); // this must be aligned with the object and light position.
    // lights.push_back(light_source);

    // coordinate system
    CoordSystem cs(40.0);
    CustomSphere sphere(0.0, 0.0, 0.0, 10.0, lights, 40, 20);

    //// Main render loop

    // Set up our green background color
    static const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector.
    SetViewAsLookAt(glm::vec3(12.0f, 12.0f, 15.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while (!glfwWindowShouldClose(window))
    {
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR, 0, clear_color);
        glClearBufferfv(GL_DEPTH, 0, clear_depth);

        // Render the object

        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());

        // draw the objects
        cs.draw();
        sphere.draw();

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
