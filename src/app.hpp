#pragma once

#include "compute_program.hpp"
#include "engine.hpp"
#include "glm/ext/vector_float2.hpp"
#include "shader_program.hpp"
#include "storage_buffer.hpp"
#include "uniform_buffer.hpp"
#include "vertex_attribute_object.hpp"
#include <SDL3/SDL_video.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <vector>

class App
{
public:
    App();
    void run();

private:
    struct Circle
    {
        glm::vec2 pos;
        float radius;
        alignas(16) glm::vec4 color;
        glm::vec2 velocity;
    };

    const std::string m_window_title = "OpenGLApp";
    const int m_init_window_width = 1000;
    const int m_init_window_height = 800;

    bool m_is_app_running = true;

    Engine m_engine;

    std::vector<float> m_vertices = {
        1.0,  1.0,  0.0,  //
        1.0,  -1.0, 0.0,  //
        -1.0, -1.0, 0.0f, //
        -1.0, 1.0,  0.0f  //
    };

    std::vector<int> m_indices = {
        0, 1, 3, //
        1, 2, 3  //
    };

    std::vector<Circle> m_circles = {
        Circle{
            glm::vec2(700.0, 700.0),
            100.0,
            glm::vec4(1.0, 0.0, 0.0, 1.0),
            glm::vec2(0.0, 0.0),
        },
        Circle{
            glm::vec2(300.0, 400.0),
            50.0,
            glm::vec4(0.0, 1.0, 0.0, 1.0),
            glm::vec2(0.0, 0.0),
        },
    };

private:
    void render(ShaderProgram shader_program, ComputeProgram compute_program, VertexAttributeObject vao, UniformBuffer uniform,
                std::vector<float> uniform_data, StorageBuffer<Circle> ssbo);
    void events();
};