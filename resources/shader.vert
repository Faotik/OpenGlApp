#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

layout(std140, binding = 0) uniform UniformBuffer
{
    mat4 view;
    mat4 projection;
    int ssbo_index;
    int world_size;
    uint rule_alive;
    uint rule_dead;
    int rule_lifespan;
    int rule_neighbourhood;
};

struct Cell
{
    int time_left;
    int is_active;
    int neighbours;
};

layout(std430, binding = 0) buffer ssbo0
{
    Cell cells0[];
};

layout(std430, binding = 1) buffer ssbo1
{
    Cell cells1[];
};

out vec3 out_color;
flat out int out_skip;
out vec3 out_normal;
out vec3 out_pos;
out float out_ambient;

int get_cell(int x, int y, int z)
{
    if (x < 0 || y < 0 || z < 0 || x >= world_size || y >= world_size || z >= world_size)
    {
        return 0;
    }

    int index = x + y * world_size + z * world_size * world_size;

    if (ssbo_index == 0 && cells0[index].is_active == 1)
    {
        return 1;
    }
    if (ssbo_index == 1 && cells1[index].is_active == 1)
    {
        return 1;
    }

    return 0;
}

void main()
{
    int id = gl_InstanceID;

    if (ssbo_index == 0 && cells0[id].is_active == 0)
    {
        gl_Position = vec4(0.0);
        out_color = vec3(0.0);
        out_skip = 1;
        return;
    }
    if (ssbo_index == 1 && cells1[id].is_active == 0)
    {
        gl_Position = vec4(0.0);
        out_color = vec3(0.0);
        out_skip = 1;
        return;
    }

    int x = id % world_size;
    int y = (id / world_size) % world_size;
    int z = id / (world_size * world_size);

    vec3 offset = vec3(x, y, z);
    offset -= world_size * 0.5;

    gl_Position = projection * view * vec4(pos.xyz + offset, 1.0);

    float t = (distance(vec3(world_size / 2, world_size / 2, world_size / 2), vec3(x, y, z))) / (world_size / 2 * sqrt(3.0));
    t = mod((t * 10), 2);
    if (t > 1) {
        t = 2-t;
    }

    vec3 color0 = vec3(64.0, 112.0, 255.0) / 255.0;
    vec3 color1 = vec3(255.0, 0.0, 0.0) / 255.0;
    vec3 color2 = vec3(255.0, 229.0, 0.0) / 255.0;
    vec3 color3 = vec3(83.0, 232.0, 237.0) / 255.0;

    //out_color = vec3(1.0, 1.0, 1.0);
    out_color = color0 * ((1 - t) * (1 - t) * (1 - t)) + color1 * 3 * ((1-t) * (1-t)) * t + color2 * 3 * (t * t) * (1-t) + color3 * t * t * t;

    //    out_color = mix(vec3(0.5, 1.0, 0.3), vec3(0.2, 0.5, 0.8), float(cells0[id].neighbours) /
    //    27); out_color = vec3(x / float(world_size), y / float(world_size), z /
    //    float(world_size)); out_color = mix(vec3(0.3, 0.3, 0.3), vec3(x / float(world_size), y /
    //    float(world_size), z / float(world_size)), float(cells0[id].neighbours) / 27);
    out_skip = 0;
    out_normal = normal;
    out_pos = pos;

    int count = 0;
    count += get_cell(int(ceil(pos.x)) + x, int(ceil(pos.y)) + y, int(ceil(pos.z)) + z);
    count += get_cell(int(ceil(pos.x)) + x, int(ceil(pos.y)) + y, int(floor(pos.z)) + z);
    count += get_cell(int(ceil(pos.x)) + x, int(floor(pos.y)) + y, int(floor(pos.z)) + z);
    count += get_cell(int(floor(pos.x)) + x, int(floor(pos.y)) + y, int(floor(pos.z)) + z);
    count += get_cell(int(ceil(pos.x)) + x, int(floor(pos.y)) + y, int(ceil(pos.z)) + z);
    count += get_cell(int(floor(pos.x)) + x, int(ceil(pos.y)) + y, int(ceil(pos.z)) + z);
    count += get_cell(int(floor(pos.x)) + x, int(floor(pos.y)) + y, int(ceil(pos.z)) + z);
    count += get_cell(int(floor(pos.x)) + x, int(ceil(pos.y)) + y, int(floor(pos.z)) + z);

    if (count <= 4){
        out_ambient = 0.0;
    }
    else{
        out_ambient = float(count - 4) / 4.0;
    }
    //out_ambient = float(count) / 8.0;
}
