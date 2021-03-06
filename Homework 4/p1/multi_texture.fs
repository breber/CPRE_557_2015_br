#version 410 core

//  Group:
//  Brian R., breber@iastate.edu
//  Arko B., abasu@iastate.edu
//  Sindhusha D., dsindhu@iastate.edu

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

in vec2 pass_TexCoord;
in vec4 pass_Color;
out vec4 color;

void main(void)
{
    // This function finds the color component for each texture coordinate.
    vec4 tex1 = texture(texture1, pass_TexCoord);
    vec4 tex2 = texture(texture2, pass_TexCoord);
    vec4 tex3 = texture(texture3, pass_TexCoord);

    // Blend the texture colors together
    color = 0.3 * tex1 + 0.3 * tex2 + 0.3 * tex3;

    // color = tex1 * tex2 * tex3;
    // color = 0.3 * pass_Color * (tex1.r + tex2.g + tex3.b);
    // color = 0.3 * pass_Color * (tex1.b + tex2.b + tex3.b);
    // color = tex2.r * tex1;
    //
    // color = .5 * tex1 + .85 * tex2;
}
