#include "vertex_buffer.hpp"
#include <iostream>
#include <vector>

VertexBuffer::VertexBuffer(const std::vector<float> &data, DRAW_TYPE draw_type, const std::vector<VertexAttributeData> attribute_data)
    : m_attribute_data(attribute_data)
{
    glGenBuffers(1, &m_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), static_cast<GLenum>(draw_type));
}