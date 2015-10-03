//
//  hw3_p2.cpp
//  Part 2 of HW3
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

CustomSphere
build_sphere_1() {
    std::vector< GLSpotLightSource > lights;
    GLSpotLightSource light_source;

    // TODO: define lights
    light_source._lightPos = glm::vec4(25.0, 25.0, 0.0, 0.0);
    light_source._ambient_intensity = 10.0;
    light_source._specular_intensity = 0.0;
    light_source._diffuse_intensity = 0.0;
    light_source._attenuation_coeff = 0.02;

    light_source._cone_angle = 4.0; // in degree
    light_source._cone_direction = glm::vec3(-1.0, -1.0, 0.0); // this must be aligned with the object and light position.
    lights.push_back(light_source);

    return CustomSphere(
        -20.0,                  // x
        0.0,                    // y
        0.0,                    // z
        5.0,                    // radius
        lights,                 // the lights to use
        "../p1/multilight.vs",  // the vertex shader
        "../p1/multilight.fs",  // the fragment shader
        50,                     // rows in the model
        50                      // segments in the model
    );
}

CustomSphere
build_sphere_2() {
    std::vector< GLSpotLightSource > lights;
    GLSpotLightSource light_source;

    // TODO: define lights
    light_source._lightPos = glm::vec4(25.0, 25.0, 0.0, 0.0);
    light_source._ambient_intensity = 10.0;
    light_source._specular_intensity = 0.0;
    light_source._diffuse_intensity = 0.0;
    light_source._attenuation_coeff = 0.02;

    light_source._cone_angle = 4.0; // in degree
    light_source._cone_direction = glm::vec3(-1.0, -1.0, 0.0); // this must be aligned with the object and light position.
    lights.push_back(light_source);

    return CustomSphere(
        -7.0,                   // x
        0.0,                    // y
        0.0,                    // z
        5.0,                    // radius
        lights,                 // the lights to use
        "../p1/multilight.vs",  // the vertex shader
        "../p1/multilight.fs",  // the fragment shader
        50,                     // rows in the model
        50                      // segments in the model
    );
}

CustomSphere
build_sphere_3() {
    std::vector< GLSpotLightSource > lights;
    GLSpotLightSource light_source;

    // TODO: define lights
    light_source._lightPos = glm::vec4(25.0, 25.0, 0.0, 0.0);
    light_source._ambient_intensity = 10.0;
    light_source._specular_intensity = 0.0;
    light_source._diffuse_intensity = 0.0;
    light_source._attenuation_coeff = 0.02;

    light_source._cone_angle = 4.0; // in degree
    light_source._cone_direction = glm::vec3(-1.0, -1.0, 0.0); // this must be aligned with the object and light position.
    lights.push_back(light_source);

    return CustomSphere(
        7.0,                    // x
        0.0,                    // y
        0.0,                    // z
        5.0,                    // radius
        lights,                 // the lights to use
        "../p1/multilight.vs",  // the vertex shader
        "../p1/multilight.fs",  // the fragment shader
        50,                     // rows in the model
        50                      // segments in the model
    );
}

CustomSphere
build_sphere_4() {
    std::vector< GLSpotLightSource > lights;
    GLSpotLightSource light_source;

    // TODO: define lights
    light_source._lightPos = glm::vec4(25.0, 25.0, 0.0, 0.0);
    light_source._ambient_intensity = 10.0;
    light_source._specular_intensity = 3.0;
    light_source._diffuse_intensity = 0.0;
    light_source._attenuation_coeff = 0.02;

    light_source._cone_angle = 4.0; // in degree
    light_source._cone_direction = glm::vec3(-1.0, -1.0, 0.0); // this must be aligned with the object and light position.
    lights.push_back(light_source);

    return CustomSphere(
        20.0,                   // x
        0.0,                    // y
        0.0,                    // z
        5.0,                    // radius
        lights,                 // the lights to use
        "../p1/multilight.vs",  // the vertex shader
        "../p1/multilight.fs",  // the fragment shader
        50,                     // rows in the model
        50                      // segments in the model
    );
}

int main(int argc, const char * argv[])
{
    // Init glfw, create a window, and init glew

    // Init the GLFW Window
    window = initWindow();

    // Init the glew api
    initGlew();

    // coordinate system
    CoordSystem cs(40.0);

    CustomSphere sphere1(build_sphere_1());
    CustomSphere sphere2(build_sphere_2());
    CustomSphere sphere3(build_sphere_3());
    CustomSphere sphere4(build_sphere_4());

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
        sphere1.draw();
        sphere2.draw();
        sphere3.draw();
        sphere4.draw();

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
