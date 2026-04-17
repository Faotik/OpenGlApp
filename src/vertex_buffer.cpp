#pragma once

#include <utility>
#include <vertex_buffer.hpp>

VertexBuffer::VertexBuffer(std::span<float> data,
                           Engine::BUFFER_DRAW_TYPE draw_type,
                           std::vector<VertexAttributeData> attribute_data)
    : m_attribute_data(std::move(attribute_data))
{
    glGenBuffers(1, &m_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<int64_t>(data.size_bytes()),
                 data.data(),
                 static_cast<GLenum>(draw_type));
}

VertexBuffer::VertexBuffer(int64_t size_bytes,
                           Engine::BUFFER_DRAW_TYPE draw_type,
                           std::vector<VertexAttributeData> attribute_data)
    : m_attribute_data(std::move(attribute_data))
{
    glGenBuffers(1, &m_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size_bytes, nullptr, static_cast<GLenum>(draw_type));
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
}

void VertexBuffer::update(std::span<float> data, int64_t offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
    glBufferSubData(GL_ARRAY_BUFFER, offset, static_cast<int64_t>(data.size_bytes()), data.data());
}
