#include "index_buffer.hpp"

IndexBuffer::IndexBuffer(std::vector<int> &data, DRAW_TYPE draw_type)
{
    glGenBuffers(1, &m_index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), data.data(), static_cast<GLenum>(draw_type));
}