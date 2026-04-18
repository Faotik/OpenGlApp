#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in mat4 model;

layout(std140, binding = 0) uniform UniformBuffer {
    mat4 view;
    mat4 projection;
    int ssbo_index;
    int world_size;
};

struct Cell
{
    int time_left;
    int is_active;
};

layout(std430, binding = 0) buffer ssbo0 {
    Cell cells0[];
};

layout(std430, binding = 1) buffer ssbo1 {
    Cell cells1[];
};

out vec3 out_color;
flat out int skip;

void main()
{
    int id = gl_InstanceID;

    if (ssbo_index == 0 && cells0[id].is_active == 0) {
        gl_Position = vec4(0.0);
        out_color = color;
        skip = 1;
        return;
    }
    if (ssbo_index == 1 && cells1[id].is_active == 0) {
        gl_Position = vec4(0.0);
        out_color = color;
        skip = 1;
        return;
    }

    int x = id % world_size;
    int y = (id / world_size) % world_size;
    int z = id / (world_size * world_size);

    vec3 offset = vec3(x, y, z);
    offset -= world_size * 0.5;

    gl_Position = projection * view * vec4(pos.xyz + offset, 1.0);
    out_color = color;
    skip = 0;
}
