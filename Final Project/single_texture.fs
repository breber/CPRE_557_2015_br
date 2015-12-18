#version 330 core

//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

uniform sampler2D tex;
uniform int texture_blend;

in vec2 pass_TexCoord;
in vec4 pass_Color;
out vec4 color;

void main(void)
{
    // This function finds the color component for each texture coordinate.
    vec4 tex_color = texture(tex, pass_TexCoord);
    if (texture_blend == 0)
    {
        color = pass_Color;
    }
    else
    {
        color = tex_color;
    }
}
