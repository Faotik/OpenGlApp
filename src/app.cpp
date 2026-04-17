#include "app.hpp"
#include "engine.hpp"
#include "index_buffer.hpp"
#include "shader_program.hpp"
#include "uniform_buffer.hpp"
#include "vertex_attribute_object.hpp"
#include "vertex_buffer.hpp"
#include <SDL3/SDL_init.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <vertex_attribute_data.hpp>

App::App()
{
    m_engine.init(m_window_title, m_init_window_width, m_init_window_height);
}

void App::run()
{
    ShaderProgram shader_program("resources/shader.vert", "resources/shader.frag");

    VertexAttributeData attribute_data_pos(0, 3, GL_FALSE, 6 * sizeof(float), nullptr);
    VertexAttributeData attribute_data_col(
        1, 3, GL_FALSE, 6 * sizeof(float), (const void *)(3 * sizeof(float)));
    VertexBuffer vertex_vbo(m_vertices,
                            Engine::BUFFER_DRAW_TYPE::STATIC_DRAW,
                            {attribute_data_pos, attribute_data_col});
    IndexBuffer ibo(m_indices, IndexBuffer::DRAW_TYPE::STATIC_DRAW);

    std::vector<VertexAttributeData> attribute_data_mat_vector;
    for (size_t i = 0; i < 4; i++)
    {
        VertexAttributeData attribute_data_mat(
            2 + i, 4, GL_FALSE, sizeof(glm::mat4), (const void *)(i * sizeof(float)), 1);
        attribute_data_mat_vector.push_back(attribute_data_mat);
    }

    VertexBuffer instance_vbo(static_cast<int64_t>(sizeof(glm::mat4)) * m_cube_count,
                              Engine::BUFFER_DRAW_TYPE::DYNAMIC_DRAW,
                              attribute_data_mat_vector);
    std::vector vbos{vertex_vbo, instance_vbo};
    VertexAttributeObject vao(vbos, ibo);

    UniformBuffer<Uniforms> uniform(sizeof(Uniforms), Engine::BUFFER_DRAW_TYPE::DYNAMIC_DRAW);

    while (m_is_app_running)
    {
        events();
        render(shader_program, vao, uniform);
    }
}

void App::render(ShaderProgram shader_program,
                 VertexAttributeObject vao,
                 UniformBuffer<Uniforms> uniform,
                 VertexBuffer instance_vbo)
{
    m_engine.clear_window();

    glm::mat4 view;
    glm::vec3 camPos(3.0f, 3.0f, -3.0f);
    glm::vec3 camTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);
    view = glm::lookAt(camPos, camTarget, camUp);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            static_cast<float>(m_init_window_width) /
                                                static_cast<float>(m_init_window_height),
                                            0.1f,
                                            100.0f);

    Uniforms uniform_data(view, projection);
    uniform.update(uniform_data, 0);
    uniform.bind(0);

    std::vector<glm::mat4> models;
    for (int64_t i = 0; i < m_cube_count; i++)
    {
        glm::mat4 model(1.0f);
        model = glm::rotate(
            model, m_engine.get_time_seconds() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        models.push_back(model);
    }
    instance_vbo.update(models);

    shader_program.use();
    vao.bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);

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
