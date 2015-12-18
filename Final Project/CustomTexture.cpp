//
//  CustomTexture.cpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

#include "CustomTexture.h"

CustomTexture::CustomTexture()
    : _texture( 0 )
    , _texture_blend_mode( 0 )
    , _textureIdx( -1 )
    , _textureBlendModelIdx( -1 )
    , _activeTexture( 0 )
{
}

CustomTexture::~CustomTexture()
{
}

int CustomTexture::loadAndCreateTexture(string path_and_file_texture, int activeTexture)
{
    unsigned int channels;
    unsigned int width;
    unsigned int height;

    unsigned char* data = loadBitmapFile(path_and_file_texture, channels, width, height);

    if (data == NULL) {
        return -1;
    }

    _activeTexture = activeTexture;

    // Texture generation - background

    // Activate a texture unit
    glActiveTexture(_activeTexture);

    // Generate a texture, this function allocates the memory and
    // associates the texture with a variable.
    glGenTextures(1, &_texture);

    // Set a texture as active texture.
    glBindTexture(GL_TEXTURE_2D, _texture);

    // Change the parameters of your texture units.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

    // Create a texture and load it to your graphics hardware. This texture is automatically associated
    // with texture 0 and the textuer variable "texture" / the active texture.
    if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    } else if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
    }

    // Delete your loaded data
    free(data);

    // Return the texture.
    return _texture;
}

bool CustomTexture::addVariablesToProgram(GLuint program, int variable_index) {
    if (program == -1) {
        return false; // no program exits
    }

    GLint params;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    if (params == GL_FALSE) {
        cerr << "[GLTexture] Program " << program << " has not been linked. Textures cannot be added." << endl;
        return false;
    }

    // enable the program
    glUseProgram(program);

    // get the location of a uniform variable. Note, the program must be linked at this position.
    // location of the texture in the glsl program
    _textureIdx = glGetUniformLocation(program, _glsl_names[0].c_str() );
    checkUniform(_textureIdx, _glsl_names[0]);

    _textureBlendModelIdx = glGetUniformLocation(program, _glsl_names[1].c_str() );
    checkUniform(_textureBlendModelIdx, _glsl_names[1]);

    // Link the texture to the uniform variable and texture unit

    // glActiveTexture tells OpenGL which texture unit we want to use
    glActiveTexture(_activeTexture);

    // We use glBindTexture bind our texture into the active texture unit.
    glBindTexture(GL_TEXTURE_2D, _texture);

    // Then we set the tex uniform of the shaders to the index of the texture unit
    glUniform1i(_textureIdx, _activeTexture - GL_TEXTURE0);
    glUniform1i(_textureBlendModelIdx, _texture_blend_mode);

    return true;
}
