#include "app.hpp"
#include "buffer.hpp"
#include "engine.hpp"
#include "shader_program.hpp"
#include "vertex_attribute_object.hpp"

#include <SDL3/SDL_init.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <vertex_attribute_data.hpp>
#include <vertex_buffer.hpp>

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
    VertexBuffer vertex_vbo(m_vertices.data(),
                            m_vertices.size() * sizeof(float),
                            Buffer::DRAW_TYPE::STATIC_DRAW,
                            {attribute_data_pos, attribute_data_col});
    Buffer ibo(Buffer::BUFFER_TYPE::INDEX_BUFFER,
               m_indices.data(),
               m_indices.size() * sizeof(int),
               Buffer::DRAW_TYPE::STATIC_DRAW);

    std::vector<VertexAttributeData> attribute_data_mat_vector;
    for (size_t i = 0; i < 4; i++)
    {
        VertexAttributeData attribute_data_mat(
            2 + i, 4, GL_FALSE, sizeof(glm::mat4), (void *)(i * sizeof(glm::vec4)), 1);
        attribute_data_mat_vector.push_back(attribute_data_mat);
    }

    VertexBuffer instance_vbo(nullptr,
                              sizeof(glm::mat4) * m_cube_count,
                              Buffer::DRAW_TYPE::DYNAMIC_DRAW,
                              attribute_data_mat_vector);
    std::vector vbos{vertex_vbo, instance_vbo};
    VertexAttributeObject vao(vbos, ibo);

    Buffer shader_uniforms(Buffer::BUFFER_TYPE::UNIFORM_BUFFER,
                           nullptr,
                           sizeof(ShaderUniforms),
                           Buffer::DRAW_TYPE::DYNAMIC_DRAW);

    glEnable(GL_DEPTH_TEST);

    while (m_is_app_running)
    {
        events();
        render(shader_program, vao, shader_uniforms, instance_vbo);
    }
}

void App::render(ShaderProgram &shader_program,
                 VertexAttributeObject &vao,
                 Buffer &shader_uniforms,
                 VertexBuffer &instance_vbo)
{
    m_engine.clear_window();

    glm::vec3 camPos(3.0f, 3.0f, -3.0f);
    glm::vec3 camTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(camPos, camTarget, camUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            static_cast<float>(m_init_window_width) /
                                                static_cast<float>(m_init_window_height),
                                            0.1f,
                                            100.0f);

    ShaderUniforms uniform_data(view, projection);
    shader_uniforms.update(&uniform_data, sizeof(ShaderUniforms));
    shader_uniforms.bind_base(0);

    std::vector<glm::mat4> models(m_cube_count);
    for (size_t i = 0; i < m_cube_count; i++)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, i * 1.5f));
        model = glm::rotate(
            model, m_engine.get_time_seconds() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        models[i] = model;
    }
    instance_vbo.update(models.data(), models.size() * sizeof(glm::mat4), 0);

    shader_program.use();
    vao.bind();

    glDrawElementsInstanced(GL_TRIANGLES,
                            static_cast<GLsizei>(m_indices.size()),
                            GL_UNSIGNED_INT,
                            nullptr,
                            static_cast<GLsizei>(m_cube_count));

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
