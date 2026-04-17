#pragma once

#include "engine.hpp"
#include "shader_program.hpp"
#include "uniform_buffer.hpp"
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
    struct Uniforms
    {
        glm::mat4x4 view;
        glm::mat4x4 projection;
    };

    const std::string m_window_title = "OpenGLApp";
    const int m_init_window_width = 1000;
    const int m_init_window_height = 800;

    bool m_is_app_running = true;

    Engine m_engine;

    const int64_t m_cube_count = 100;

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
    void render(ShaderProgram shader_program,
                VertexAttributeObject vao,
                UniformBuffer<Uniforms> uniform);
    void events();
};