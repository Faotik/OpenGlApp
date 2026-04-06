#include "shader_program.hpp"
#include "shader.hpp"
#include <glad/glad.h>

ShaderProgram::ShaderProgram(const std::vector<std::reference_wrapper<Shader>> &shaders) : m_shader_program(glCreateProgram())
{
    for (const auto &shader : shaders)
    {
        glAttachShader(m_shader_program, shader.get().m_shader);
    }

    glLinkProgram(m_shader_program);
}

void ShaderProgram::use()
{
    glUseProgram(m_shader_program);
}