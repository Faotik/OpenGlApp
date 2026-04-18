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
    Buffer ibo(Buffer::BUFFER_TYPE::INDEX_BUFFER,
               m_indices.data(),
               m_indices.size() * sizeof(int),
               Buffer::DRAW_TYPE::STATIC_DRAW);

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
    VertexAttributeObject vao(vbos, ibo);

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

    std::vector cells(m_world_size * m_world_size * m_world_size, Cell{m_rule_lifespan_count, 0});

    for (uint64_t x = m_world_size / 2 - 2; x <= m_world_size / 2 + 2; x++)
    {
        for (uint64_t y = m_world_size / 2 - 2; y <= m_world_size / 2 + 2; y++)
        {
            for (uint64_t z = m_world_size / 2 - 2; z <= m_world_size / 2 + 2; z++)
            {
                if (rand() % 2 == 0)
                {
                    cells[x + y * m_world_size + z * m_world_size * m_world_size].is_active = 1;
                }
            }
        }
    }

    shader_ssbo0.update(cells.data(), cells.size() * sizeof(Cell));
    shader_ssbo1.update(cells.data(), cells.size() * sizeof(Cell));

    while (m_is_app_running)
    {
        events();
        // tick();
        render(shader_program, compute_program, vao, shader_uniforms, shader_ssbo0, shader_ssbo1);
    }
}

// uint64_t App::sat_add(uint64_t a, uint64_t b)
// {
//     uint64_t result = a + b;
//     if (result < a)
//         return std::numeric_limits<uint64_t>::max();
//     return result;
// }
//
// uint64_t App::sat_sub(uint64_t a, uint64_t b)
// {
//     if (a < b)
//         return 0;
//     return a - b;
// }
//
// uint64_t App::count_neighbours(uint64_t _x, uint64_t _y, uint64_t _z)
// {
//     uint64_t count = 0;
//
//     for (uint64_t x = sat_sub(_x, 1); x < sat_add(_x, 1); x++)
//     {
//         for (uint64_t y = sat_sub(_y, 1); y < sat_add(_y, 1); y++)
//         {
//             for (uint64_t z = sat_sub(_z, 1); z < sat_add(_z, 1); z++)
//             {
//                 if ((x == _x && y == _y && z == _z) || x >= m_world_size || y >= m_world_size ||
//                     z >= m_world_size)
//                 {
//                     continue;
//                 }
//
//                 if (m_cells_old[x + y * m_world_size + z * m_world_size *
//                 m_world_size].is_active)
//                 {
//                     count++;
//                 }
//             }
//         }
//     }
//
//     return count;
// }
//
// void App::tick()
// {
//     m_models.clear();
//
// for (uint64_t x = 0; x < m_world_size; x++)
// {
//     for (uint64_t y = 0; y < m_world_size; y++)
//     {
//         for (uint64_t z = 0; z < m_world_size; z++)
//         {
//             uint64_t count = count_neighbours(x, y, z);
//
//             if (m_cells_old[x + y * m_world_size + z * m_world_size *
//             m_world_size].is_active)
//             {
//                 if (!std::ranges::contains(rule_survival_count, count) ||
//                     (m_cells_old[x + y * m_world_size + z * m_world_size * m_world_size]
//                              .time_left < rule_lifespan_count &&
//                      m_cells_old[x + y * m_world_size + z * m_world_size * m_world_size]
//                              .time_left > 0))
//                 {
//                     m_cells[x + y * m_world_size + z * m_world_size *
//                     m_world_size].time_left--;
//                 }
//                 if (m_cells_old[x + y * m_world_size + z * m_world_size * m_world_size]
//                         .time_left == 0)
//                 {
//                     m_cells[x + y * m_world_size + z * m_world_size * m_world_size].is_active
//                     =
//                         false;
//                 }
//             }
//             else
//             {
//                 if (std::ranges::contains(rule_birth_count, count))
//                 {
//                     m_cells[x + y * m_world_size + z * m_world_size * m_world_size].time_left
//                     =
//                         rule_lifespan_count;
//                     m_cells[x + y * m_world_size + z * m_world_size * m_world_size].is_active
//                     =
//                         true;
//                 }
//             }
//
//             if (m_cells[x + y * m_world_size + z * m_world_size * m_world_size].is_active)
//             {
//                 glm::mat4 model(1.0f);
//                 model = glm::translate(model,
//                                        glm::vec3(-(m_world_size * 0.5),
//                                                  -(m_world_size * 0.5),
//                                                  -(m_world_size * 0.5)));
//                 model = glm::translate(model, glm::vec3(x, y, z));
//
//                 m_models.push_back(model);
//             }
//         }
//     }
// }
//
//     m_cells_old = m_cells;
// }

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

    glm::vec3 camPos(static_cast<float>(m_world_size),
                     static_cast<float>(m_world_size),
                     -static_cast<float>(m_world_size));
    glm::vec3 camTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(camPos, camTarget, camUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            static_cast<float>(m_init_window_width) /
                                                static_cast<float>(m_init_window_height),
                                            0.1f,
                                            1000.0f);

    ShaderUniforms uniform_data(view, projection, m_ssbo_index, m_world_size);
    shader_uniforms.update(&uniform_data, sizeof(ShaderUniforms));
    shader_uniforms.bind_base(0);

    shader_ssbo1.bind_base(0);
    shader_ssbo2.bind_base(1);

    shader_program.use();
    vao.bind();

    glDrawElementsInstanced(GL_TRIANGLES,
                            static_cast<GLsizei>(m_indices.size()),
                            GL_UNSIGNED_INT,
                            nullptr,
                            static_cast<GLsizei>(m_world_size * m_world_size * m_world_size));

    m_engine.swap_window();

    if (m_ssbo_index == 0)
    {
        m_ssbo_index = 1;
    }
    else
    {
        m_ssbo_index = 0;
    }
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
