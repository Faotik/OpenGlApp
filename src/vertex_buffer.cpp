#include <vertex_buffer.hpp>

VertexBuffer::VertexBuffer(const void *data,
                           size_t size_bytes,
                           Buffer::DRAW_TYPE draw_type,
                           std::vector<VertexAttributeData> attribute_data)
    : m_buffer(Buffer(Buffer::BUFFER_TYPE::VERTEX_BUFFER, data, size_bytes, draw_type)),
      m_attribute_data(std::move(attribute_data))
{}

void VertexBuffer::bind() const
{
    m_buffer.bind();
}

void VertexBuffer::update(const void *data, size_t size_bytes, int64_t offset) const
{
    m_buffer.update(data, size_bytes, offset);
}

std::span<const VertexAttributeData> VertexBuffer::get_attribute_data() const
{
    return m_attribute_data;
}
