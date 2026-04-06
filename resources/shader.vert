#version 460 core

layout(std140, binding = 0) uniform data {
    float time;
};

layout(location = 0) in vec3 pos;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(pos.xyz, 1.0);
    vertexColor = vec4(0.0, cos(time*2)+1.2, cos(time*2)+1.2, 1);
}
