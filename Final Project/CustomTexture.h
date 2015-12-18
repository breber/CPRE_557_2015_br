//
//  CustomTexture.hpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

#pragma once

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// locals
#include "GLAppearanceBase.h"
#include "Texture.h"

class CustomTexture : public GLTextureBase
{
private:
    // Allow the class GLApperance access to protected variables.
    friend class GLAppearance;

    // These are the variable names which are used in our glsl shader programs.
    // Make sure that you use the correct names in your programs.
    const string _glsl_names[2] = { "tex", "texture_blend" };

public:
    CustomTexture();
    ~CustomTexture();

    /*!
     Load two bitmap images as textures from files.
     @param path_and_file_texture_1 - path and file of the first image.
     @return int - the texture id when the texture was sucessfully loaded.
     */
    int loadAndCreateTexture(string path_and_file_texture, int activeTexture);

    /*!
     This sets the texture blend model
     @return true, when a new mode was set, false when current and new mode are equal
     */
    void setTextureBlendMode(int mode)
    {
        _texture_blend_mode = mode;
    }

    /*!
     Adds the variables of this object to the shader program
     */
    virtual bool addVariablesToProgram(GLuint program, int variable_index);

    virtual bool dirty(GLuint program)
    {
        glUseProgram(program);
        glUniform1i(_textureBlendModelIdx, _texture_blend_mode);
        glUseProgram(0);

        _dirty = false;
        return true;
    }

private:
    GLuint  _texture;
    int     _texture_blend_mode;

    int     _textureIdx;
    int     _textureBlendModelIdx;

    int     _activeTexture;
};
