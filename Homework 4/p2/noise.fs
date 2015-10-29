#version 410 core

//  Group:
//  Brian R., breber@iastate.edu
//  Arko B., abasu@iastate.edu
//  Sindhusha D., dsindhu@iastate.edu

uniform sampler2D texture_background; // colorMap
uniform sampler2D texture_foreground; // noiseMap
uniform int texture_blend;

in vec2 pass_TexCoord;
in vec4 pass_Color;
out vec4 color;

void main(void)
{
    vec2 noiseVec;
    // noiseVec = normalize(texture(texture_foreground, pass_TexCoord)).gb;
    noiseVec = (noiseVec * 2.0 - 1.0) * 0.035;

    color = texture(texture_background, pass_TexCoord + noiseVec);
}
