#include <SDL3/SDL_init.h>
#include <app.hpp>

#include "../build/release/_deps/sdl3-src/include/SDL3/SDL_timer.h"

#include <buffer.hpp>
#include <engine.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <shader_program.hpp>
#include <thread>
#include <vector>
#include <vertex_attribute_data.hpp>
#include <vertex_attribute_object.hpp>
#include <vertex_buffer.hpp>

App::App()
{
    m_engine.init(m_window_title, m_init_window_width, m_init_window_height);
}

void App::run()
{
    ShaderProgram shader_program("resources/shader.vert", "resources/shader.frag");
    ComputeProgram compute_program("resources/shader.comp");

    VertexAttributeData attribute_data_pos(0, 3, GL_FALSE, 6 * sizeof(float), nullptr);
    VertexAttributeData attribute_data_col(
        1, 3, GL_FALSE, 6 * sizeof(float), (const void *)(3 * sizeof(float)));
    VertexBuffer vertex_vbo(m_vertices.data(),
                            m_vertices.size() * sizeof(float),
                            Buffer::DRAW_TYPE::STATIC_DRAW,
                            {attribute_data_pos, attribute_data_col});
    // Buffer ibo(Buffer::BUFFER_TYPE::INDEX_BUFFER,
    //            m_indices.data(),
    //            m_indices.size() * sizeof(int),
    //            Buffer::DRAW_TYPE::STATIC_DRAW);

    // std::vector<VertexAttributeData> attribute_data_mat_vector;
    // for (size_t i = 0; i < 4; i++)
    // {
    //     VertexAttributeData attribute_data_mat(
    //         2 + i, 4, GL_FALSE, sizeof(glm::mat4), (void *)(i * sizeof(glm::vec4)), 1);
    //     attribute_data_mat_vector.push_back(attribute_data_mat);
    // }

    // VertexBuffer instance_vbo(nullptr,
    //                           sizeof(glm::mat4) * m_world_size * m_world_size * m_world_size,
    //                           Buffer::DRAW_TYPE::DYNAMIC_DRAW,
    //                           attribute_data_mat_vector);
    std::vector vbos{vertex_vbo};
    VertexAttributeObject vao(vbos);

    Buffer shader_uniforms(Buffer::BUFFER_TYPE::UNIFORM_BUFFER,
                           nullptr,
                           sizeof(ShaderUniforms),
                           Buffer::DRAW_TYPE::DYNAMIC_DRAW);

    Buffer shader_ssbo0(Buffer::BUFFER_TYPE::STORAGE_BUFFER,
                        nullptr,
                        sizeof(Cell) * m_world_size * m_world_size * m_world_size,
                        Buffer::DRAW_TYPE::DYNAMIC_DRAW);

    Buffer shader_ssbo1(Buffer::BUFFER_TYPE::STORAGE_BUFFER,
                        nullptr,
                        sizeof(Cell) * m_world_size * m_world_size * m_world_size,
                        Buffer::DRAW_TYPE::DYNAMIC_DRAW);

    glEnable(GL_DEPTH_TEST);

    std::vector cells(m_world_size * m_world_size * m_world_size, Cell{m_rule_lifespan, 0, 0});

    // for (uint64_t x = m_world_size / 2 - 10; x <= m_world_size / 2 + 10; x++)
    // {
    //     for (uint64_t y = m_world_size / 2 - 10; y <= m_world_size / 2 + 10; y++)
    //     {
    //         for (uint64_t z = m_world_size / 2 - 10; z <= m_world_size / 2 + 10; z++)
    //         {
    //             if (rand() % 10 > 3)
    //             {
    //                 size_t index = x + y * m_world_size + z * m_world_size * m_world_size;
    //                 cells[index].is_active = 1;
    //                 // if (rand() % 2 == 0)
    //                 // {
    //                 //     cells[index].time_left = rand() % m_rule_lifespan;
    //                 // }
    //             }
    //         }
    //     }
    // }

    // cells[20 + 20 * m_world_size + 20 * m_world_size * m_world_size].is_active = 1;
    // cells[21 + 20 * m_world_size + 20 * m_world_size * m_world_size].is_active = 1;
    // cells[20 + 21 * m_world_size + 20 * m_world_size * m_world_size].is_active = 1;
    // cells[21 + 21 * m_world_size + 20 * m_world_size * m_world_size].is_active = 1;

    cells[m_world_size / 2 + m_world_size / 2 * m_world_size +
          m_world_size / 2 * m_world_size * m_world_size]
        .is_active = 1;

    shader_ssbo0.update(cells.data(), cells.size() * sizeof(Cell));
    shader_ssbo1.update(cells.data(), cells.size() * sizeof(Cell));

    while (m_is_app_running)
    {
        events();
        render(shader_program, compute_program, vao, shader_uniforms, shader_ssbo0, shader_ssbo1);
    }
}

void App::render(ShaderProgram &shader_program,
                 ComputeProgram &compute_program,
                 VertexAttributeObject &vao,
                 Buffer &shader_uniforms,
                 Buffer &shader_ssbo1,
                 Buffer &shader_ssbo2)
{
    compute_program.use_and_dispatch(std::ceil(m_world_size / 8.0),
                                     std::ceil(m_world_size / 8.0),
                                     std::ceil(m_world_size / 8.0));
    m_engine.memory_barrier(Engine::MEMORY_BARRIER_TYPE::SHADER_STORAGE_BARRIER);

    m_engine.clear_window();

    // glm::vec3 camPos(static_cast<float>(m_world_size * 1.5),
    //                  static_cast<float>(m_world_size * 1.5),
    //                  static_cast<float>(m_world_size * 1.5));
    glm::vec3 camPos(
        static_cast<float>(std::sin(m_engine.get_time_seconds() * 0.3) * m_world_size * 1.5),
        static_cast<float>(m_world_size * 1.5),
        static_cast<float>(std::cos(m_engine.get_time_seconds() * 0.3) * m_world_size * 1.5));
    glm::vec3 camTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(camPos, camTarget, camUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            static_cast<float>(m_init_window_width) /
                                                static_cast<float>(m_init_window_height),
                                            0.1f,
                                            1000.0f);

    ShaderUniforms uniform_data(view,
                                projection,
                                m_ssbo_index,
                                m_world_size,
                                m_rule_alive,
                                m_rule_dead,
                                m_rule_lifespan,
                                m_rule_neighbourhood);
    shader_uniforms.update(&uniform_data, sizeof(ShaderUniforms));
    shader_uniforms.bind_base(0);

    shader_ssbo1.bind_base(0);
    shader_ssbo2.bind_base(1);

    shader_program.use();
    vao.bind();

    glDrawArraysInstanced(
        GL_TRIANGLES, 0, 36, static_cast<GLsizei>(m_world_size * m_world_size * m_world_size));

    m_engine.swap_window();

    if (m_ssbo_index == 0)
    {
        m_ssbo_index = 1;
    }
    else
    {
        m_ssbo_index = 0;
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
