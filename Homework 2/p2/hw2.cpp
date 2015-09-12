//
//  hw2.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
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

// glfw includes
#include <GLFW/glfw3.h>

// include local files
#include "controls.h"
#include "HCI557Common.h"

using namespace std;

static const string vs_string =
"#version 410 core                                              \n"
"                                                               \n"
"uniform mat4 projectionMatrix;                                 \n"
"uniform mat4 viewMatrix;                                       \n"
"uniform mat4 modelMatrix;                                      \n"
"in vec3 in_Position;                                           \n"
"                                                               \n"
"in vec3 in_Color;                                              \n"
"out vec3 pass_Color;                                           \n"
"                                                               \n"
"void main(void)                                                \n"
"{                                                              \n"
"    gl_Position = projectionMatrix * viewMatrix *                "
"                       modelMatrix * vec4(in_Position, 1.0);   \n"
"    pass_Color = in_Color;                                     \n"
"}                                                              \n";

// Fragment shader source code. This determines the colors in the
// fragment generated in the shader pipeline. In this case, it
// colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                              \n"
"                                                               \n"
"in vec3 pass_Color;                                            \n"
"out vec4 color;                                                \n"
"                                                               \n"
"void main(void)                                                \n"
"{                                                              \n"
"    color = vec4(pass_Color, 1.0);                             \n"
"}                                                              \n";

/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix;       // Store the view matrix
glm::mat4 modelMatrix;      // Store the model matrix

// The handle to the window object
GLFWwindow* window;

// Define some of the global variables we're using for this sample
GLuint program;

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

/*
    Create the model using triangle strips
*/
unsigned int createTriangleStripModel()
{
    // TODO: use the vertex array object vaoID[0] for this model representation

    return 1;
}

/*
    Create the model using other primitives
*/
unsigned int createMyModel()
{
    // TODO: use the vertex array object vaoID[1] for this model representation

    return 1;
}



/*
    Render the triangle strip model
*/
void renderTriangleStripModel()
{
    // TODO
}

/*!
    Render the other primitive model
 */
void renderMyModel()
{
    // TODO
}

/*
    Create the two models
*/
void setupScene()
{
    createTriangleStripModel();
    createMyModel();
}

/*
    Update the virtual camera
*/
bool updateCamera()
{
    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    viewMatrix =  getViewMatrix(); // get the current view matrix

    return true;
}

int main(int argc, const char * argv[])
{
    //// Init glfw, create a window, and init glew

    // Init the GLFW Window
    window = initWindow();

    // Init the glew api
    initGlew();

    //// The Shader Program starts here

    // Vertex shader source code. This draws the vertices in our window. We have
    // 3 vertices since we're drawing an triangle. Each vertex is represented by
    // a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();

    // Fragment shader source code. This determines the colors in the fragment
    // generated in the shader pipeline. In this case, it colors the inside
    // of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();

    // This next section we'll generate the OpenGL program and attach the
    // shaders to it so that we can render our triangle.
    program = glCreateProgram();

    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);

    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);

    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);

    //// The Shader Program ends here

    //// Set up the virtual camera

    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader

    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");

    //// Finish setting up the virtual camera

    // this creates the scene
    setupScene();

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we
    // proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);

    // This is our render loop. As long as our window remains open
    // (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);

        // update the virtual camera
        // ignore this line since we did not introduced cameras.
        updateCamera();

        //// Generate the object
        // Enable the shader program
        glUseProgram(program);

        // this changes the camera location
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // send the view matrix to our shader

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

        renderTriangleStripModel();

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

        renderMyModel();

        glUseProgram(0);
        //// End generate the object

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}
