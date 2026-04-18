#pragma once

#include "engine.hpp"
#include "shader_program.hpp"
#include "vertex_attribute_object.hpp"
#include <glm/mat4x4.hpp>

#include <string>
#include <vector>

class App
{
public:
    App();
    void run();

private:
    struct CameraUniforms
    {
        glm::mat4x4 view;
        glm::mat4x4 projection;
    };

    struct Cell
    {
        uint64_t time_left;
        bool is_active;
    };

    const size_t m_world_size = 20;

    std::vector<Cell> m_cells_old;
    std::vector<Cell> m_cells;
    std::vector<glm::mat4> m_models;

    const std::vector<uint64_t> rule_survival_count{4};
    const std::vector<uint64_t> rule_birth_count{4};
    const uint64_t rule_lifespan_count{5};
    const bool rule_neighbour_full = true;

    const std::string m_window_title = "OpenGLApp";
    const int m_init_window_width = 1000;
    const int m_init_window_height = 800;

    bool m_is_app_running = true;

    Engine m_engine;

    // clang-format off
    std::vector<float> m_vertices = {
        -0.5f,  -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // 0
        -0.5f,   0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 1
         0.5f,   0.5f, -0.5f,   0.1f, 0.1f, 0.1f, // 2
         0.5f,  -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // 3
         0.5f,  -0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // 4
         0.5f,   0.5f,  0.5f,   1.0f, 0.0f, 0.0f, // 5
        -0.5f,   0.5f,  0.5f,   0.1f, 0.1f, 0.1f, // 6
        -0.5f,  -0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // 7
    };

    std::vector<int> m_indices = {
        0, 1, 2,
        0, 2, 3,
        3, 2, 5,
        3, 5, 4,
        4, 5, 6,
        4, 6, 7,
        7, 6, 1,
        7, 1, 0,
        1, 6, 5,
        1, 5, 2,
        0, 7, 4,
        0, 4, 3,
    };
    // clang-format on

private:
    void tick();
    void render(ShaderProgram &shader_program,
                VertexAttributeObject &vao,
                Buffer &shader_uniforms,
                VertexBuffer &instance_vbo);
    uint64_t count_neighbours(uint64_t x, uint64_t y, uint64_t z);
    void events();

    uint64_t sat_add(uint64_t a, uint64_t b);
    uint64_t sat_sub(uint64_t a, uint64_t b);
};