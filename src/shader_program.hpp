#pragma once

#include "shader.hpp"
#include <vector>

class ShaderProgram
{
public:
    ShaderProgram(std::string vertex_shader_path, std::string fragment_shaders_path);
    void use();

private:
    const GLuint m_shader_program;
};