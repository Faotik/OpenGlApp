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
    float border_radius;
    float screen_width;
    float screen_height;
};

out vec4 FragColor;

void main()
{
    //vec2 Frag_CoordNorm = gl_FragCoord.xy / vec2(screen_width, screen_height) * 2.0 - 1.0;

    for(int i = 0; i < int(circle_count); i++){ 
        if (distance(gl_FragCoord.xy, circles[i].pos.xy) < circles[i].radius){
            FragColor = circles[i].color;
            return;
        }
    }

    if (distance(gl_FragCoord.xy, vec2(screen_width / 2.0, screen_height / 2.0)) > border_radius &&
        distance(gl_FragCoord.xy, vec2(screen_width / 2.0, screen_height / 2.0)) < border_radius + 20){
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        return;
    }

    discard;
}
