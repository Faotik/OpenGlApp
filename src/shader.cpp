#include "shader.hpp"
#include "engine.hpp"

Shader::Shader(SHADER_TYPE shader_type, const std::string &filename) : m_shader(glCreateShader(static_cast<GLuint>(shader_type)))
{
    std::string shader_source = Engine::read_file(filename);
    const char *src = shader_source.c_str();

    glShaderSource(m_shader, 1, &src, nullptr);
    glCompileShader(m_shader);
}

Shader::~Shader()
{
    glDeleteShader(m_shader);
}
