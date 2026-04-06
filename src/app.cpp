#include "app.hpp"
#include "compute_program.hpp"
#include "engine.hpp"
#include "index_buffer.hpp"
#include "shader_program.hpp"
#include "storage_buffer.hpp"
#include "uniform_buffer.hpp"
#include "vertex_attribute_object.hpp"
#include "vertex_buffer.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <cmath>
#include <glad/glad.h>
#include <vector>

App::App()
{
    m_engine.init(m_window_title, m_init_window_width, m_init_window_height);
}

void App::run()
{
    ShaderProgram shader_program("resources/shader.vert", "resources/shader.frag");
    ComputeProgram compute_program("resources/shader.comp");

    VertexAttributeData attribute_data(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0, 0);
    VertexBuffer vbo(m_vertices, VertexBuffer::DRAW_TYPE::STATIC_DRAW, {attribute_data});
    IndexBuffer ibo(m_indices, IndexBuffer::DRAW_TYPE::STATIC_DRAW);
    VertexAttributeObject vao(vbo, ibo);

    std::vector<float> uniform_data = {m_engine.get_time_seconds(), 0};
    UniformBuffer uniform(uniform_data, UniformBuffer::DRAW_TYPE::DYNAMIC_DRAW);

    StorageBuffer ssbo(m_circles, StorageBuffer<Circle>::DRAW_TYPE::DYNAMIC_DRAW);

    while (m_is_app_running)
    {
        events();
        render(shader_program, compute_program, vao, uniform, uniform_data, ssbo);
    }
}

void App::render(ShaderProgram shader_program, ComputeProgram compute_program, VertexAttributeObject vao, UniformBuffer uniform,
                 std::vector<float> uniform_data, StorageBuffer<Circle> ssbo)
{
    compute_program.use_and_dispatch(std::ceil(m_circles.size() / 64.0));
    m_engine.memory_barrier(Engine::MEMORY_BARRIER_TYPE::SHADER_STORAGE_BARRIER);

    m_engine.clear_window();

    uniform_data[0] = m_engine.get_time_seconds();
    uniform_data[1] = m_circles.size();
    uniform.update(uniform_data);
    uniform.bind(0);
    ssbo.bind(0);

    shader_program.use();
    vao.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);

    m_engine.swap_window();
}

void App::events()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            m_is_app_running = false;
            return;
        case SDL_EVENT_KEY_DOWN:
            switch (event.key.key)
            {
            case SDLK_ESCAPE:
                m_is_app_running = false;
                return;
            }
        }
    }
}
