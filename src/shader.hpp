#pragma once

#include <glad/glad.h>
#include <string>

enum class SHADER_TYPE
{
    VERTEX_SHADER = GL_VERTEX_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    COMPUTE_SHADER = GL_COMPUTE_SHADER,
};

class Shader
{
public:
    Shader(SHADER_TYPE shader_type, const std::string &filename);
    ~Shader();

public:
    const GLuint m_shader;
};