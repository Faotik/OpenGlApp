#include "shader_program.hpp"
#include "shader.hpp"
#include <glad/glad.h>
#include <string>

ShaderProgram::ShaderProgram(std::string vertex_shader_path, std::string fragment_shaders_path) : m_shader_program(glCreateProgram())
{
    Shader vertex_shader(SHADER_TYPE::VERTEX_SHADER, vertex_shader_path);
    Shader fragment_shader(SHADER_TYPE::FRAGMENT_SHADER, fragment_shaders_path);

    glAttachShader(m_shader_program, vertex_shader.m_shader);
    glAttachShader(m_shader_program, fragment_shader.m_shader);

    glLinkProgram(m_shader_program);
}

void ShaderProgram::use()
{
    glUseProgram(m_shader_program);
}