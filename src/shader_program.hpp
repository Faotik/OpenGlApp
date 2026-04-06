#pragma once

#include "shader.hpp"

class ShaderProgram
{
public:
    ShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path);
    void use();

private:
    const GLuint m_shader_program;
};