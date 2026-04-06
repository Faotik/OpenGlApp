#include "compute_program.hpp"
#include "shader.hpp"

ComputeProgram::ComputeProgram(std::string compute_shader_path) : m_shader_program(glCreateProgram())
{
    Shader compute_shader(SHADER_TYPE::COMPUTE_SHADER, compute_shader_path);

    glAttachShader(m_shader_program, compute_shader.m_shader);
    glLinkProgram(m_shader_program);
}

void ComputeProgram::use_and_dispatch(GLuint group_size_x, GLuint group_size_y, GLuint group_size_z)
{
    glUseProgram(m_shader_program);
    glDispatchCompute(group_size_x, group_size_y, group_size_z);
}