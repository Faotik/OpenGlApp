#pragma once

#include "engine.hpp"
#include "shader_program.hpp"
#include "vertex_attribute_object.hpp"

#include <compute_program.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <vector>

class App
{
public:
    App();
    void run();

private:
    struct ShaderUniforms
    {
        glm::mat4x4 view;
        glm::mat4x4 projection;
        int ssbo_index;
        int world_size;
        uint32_t rule_alive;
        uint32_t rule_dead;
        int rule_lifespan;
        int rule_neighbourhood;
    };

    struct Cell
    {
        int time_left;
        int is_active;
        int neighbours;
    };

    const size_t m_world_size = 200;

    // clang-format off
    // const uint32_t m_rule_alive = 0b000000000000000000000000000;
    // const uint32_t m_rule_dead  = 0b000000000000000000000000000;

    // const uint32_t m_rule_alive = 0b111111111111111111000000000;
    // const uint32_t m_rule_dead  = 0b000000000001011000011100000;

    // const uint32_t m_rule_alive = 0b000000000000000000001111111;
    // const uint32_t m_rule_dead  = 0b000000000000000000000001010;
    // const int m_rule_lifespan = 1;
    // const int m_rule_neighbourhood = 1;

    const uint32_t m_rule_alive = 0b000000000000000001001000100;
    const uint32_t m_rule_dead  = 0b000000000000000001101010000;
    const int m_rule_lifespan = 9;
    const int m_rule_neighbourhood = 0;
    // clang-format on

    const std::string m_window_title = "OpenGLApp";
    const int m_init_window_width = 1000;
    const int m_init_window_height = 800;

    bool m_is_app_running = true;
    int m_ssbo_index = 0;

    Engine m_engine;

    // clang-format off
    // std::vector<float> m_vertices = {
    //     -0.5f,  -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // 0
    //     -0.5f,   0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 1
    //      0.5f,   0.5f, -0.5f,   0.1f, 0.1f, 0.1f, // 2
    //      0.5f,  -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // 3
    //      0.5f,  -0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // 4
    //      0.5f,   0.5f,  0.5f,   1.0f, 0.0f, 0.0f, // 5
    //     -0.5f,   0.5f,  0.5f,   0.1f, 0.1f, 0.1f, // 6
    //     -0.5f,  -0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // 7
    // };
    //
    // std::vector<int> m_indices = {
    //     0, 1, 2,
    //     0, 2, 3,
    //     3, 2, 5,
    //     3, 5, 4,
    //     4, 5, 6,
    //     4, 6, 7,
    //     7, 6, 1,
    //     7, 1, 0,
    //     1, 6, 5,
    //     1, 5, 2,
    //     0, 7, 4,
    //     0, 4, 3,
    // };
    std::vector<float> m_vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // clang-format on

private:
    void tick();
    void render(ShaderProgram &shader_program,
                ComputeProgram &compute_program,
                VertexAttributeObject &vao,
                Buffer &shader_uniforms,
                Buffer &shader_ssbo1,
                Buffer &shader_ssbo2);
    uint64_t count_neighbours(uint64_t x, uint64_t y, uint64_t z);
    void events();

    uint64_t sat_add(uint64_t a, uint64_t b);
    uint64_t sat_sub(uint64_t a, uint64_t b);
};