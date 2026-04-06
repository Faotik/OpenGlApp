#pragma once

#include <glad/glad.h>
#include <string>

class ComputeProgram
{
public:
    ComputeProgram(std::string compute_shader_path);
    void use_and_dispatch(GLuint group_size_x = 1, GLuint group_size_y = 1, GLuint group_size_z = 1);

private:
    const GLuint m_shader_program;
};