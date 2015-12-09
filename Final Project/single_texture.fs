#version 410 core

//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

uniform sampler2D tex;

in vec2 pass_TexCoord;
in vec4 pass_Color;
out vec4 color;

uniform int texture_blend;

void main(void)
{
    // This function finds the color component for each texture coordinate.
    vec4 tex_color =  texture(tex, pass_TexCoord);
    color = tex_color;
}
