#version 460 core

in vec3 out_color;
flat in int skip;

out vec4 FragColor;

void main()
{
    if (skip == 1){
        discard;
    }

    FragColor = vec4(out_color.xyz, 1.0);
}
