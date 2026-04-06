#version 460 core

struct Circle
{
    vec2 pos;
    float radius;
    vec4 color;
    vec2 velocity;
};

layout(std430, binding = 0) buffer SSBOBuffer {
    Circle circles[];
};

layout(std140, binding = 0) uniform UniformBuffer {
    float time;
    float circle_count;
};

out vec4 FragColor;

void main()
{
    for(int i = 0; i < int(circle_count); i++){ 
        if (distance(gl_FragCoord.xy, circles[i].pos.xy) < circles[i].radius){
            FragColor = circles[i].color;
            return;
        }
    }

    discard;
}
