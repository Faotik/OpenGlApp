#include "storage_buffer.hpp"

StorageBuffer::StorageBuffer(std::vector<float> &data, DRAW_TYPE draw_type)
{
    glGenBuffers(1, &m_storage_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_storage_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(float), data.data(), static_cast<GLenum>(draw_type));
}

void StorageBuffer::bind(GLuint binding)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_storage_buffer);
}

void StorageBuffer::update(std::vector<float> &data)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_storage_buffer);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data.size(), data.data());
}
