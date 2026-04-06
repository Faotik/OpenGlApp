#include "uniform_buffer.hpp"

UniformBuffer::UniformBuffer(std::vector<float> &data, DRAW_TYPE draw_type)
{
    glGenBuffers(1, &m_uniform_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uniform_buffer);
    glBufferData(GL_UNIFORM_BUFFER, data.size() * sizeof(float), data.data(), static_cast<GLenum>(draw_type));
}

void UniformBuffer::bind(GLuint binding)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_uniform_buffer);
}

void UniformBuffer::update(std::vector<float> &data)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uniform_buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, data.size() * sizeof(float), data.data());
}
