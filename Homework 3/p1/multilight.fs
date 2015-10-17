#version 330 core

//  Group:
//  Brian R., breber@iastate.edu
//  Shrabya K., shrabya@iastate.edu
//  Andrew M., amaxim@iastate.edu
//  Kyle V., vansicek@iastate.edu 

in vec3 pass_Color;
out vec4 color;

void main(void)
{
    color = vec4(pass_Color, 1.0);
}
