#pragma once

#include "engine.hpp"
#include "shader_program.hpp"
#include "uniform_buffer.hpp"
#include "vertex_attribute_object.hpp"
#include <SDL3/SDL_video.h>
#include <string>
#include <vector>

class App
{
public:
    App();
    void run();

private:
    const std::string m_window_title = "OpenGLApp";
    const int m_init_window_width = 1000;
    const int m_init_window_height = 800;

    bool m_is_app_running = true;

    Engine m_engine;

    std::vector<float> m_vertices = {
        0.5f,  0.5f,  0.0f, //
        0.5f,  -0.5f, 0.0f, //
        -0.5f, -0.5f, 0.0f, //
        -0.5f, 0.5f,  0.0f  //
    };

    std::vector<int> m_indices = {
        0, 1, 3, //
        1, 2, 3  //
    };

private:
    void render(ShaderProgram shader_program, VertexAttributeObject vao, UniformBuffer uniform, std::vector<float> uniform_data);
    void events();
};