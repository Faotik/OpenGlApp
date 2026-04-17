#version 460 core

in vec3 out_color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(out_color.xyz, 1.0);
}
