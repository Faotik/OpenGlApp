#pragma once

#include "shader.hpp"
#include <vector>

class ShaderProgram
{
public:
    ShaderProgram(const std::vector<std::reference_wrapper<Shader>> &shaders);
    void use();

private:
    const GLuint m_shader_program;
};