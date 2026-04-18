#include <buffer.hpp>

Buffer::Buffer(BUFFER_TYPE buffer_type, const void *data, size_t size_bytes, DRAW_TYPE draw_type)
    : m_buffer_type(buffer_type)
{
    glGenBuffers(1, &m_buffer_id);
    glBindBuffer(static_cast<GLenum>(m_buffer_type), m_buffer_id);
    glBufferData(static_cast<GLenum>(m_buffer_type),
                 static_cast<int64_t>(size_bytes),
                 data,
                 static_cast<GLenum>(draw_type));
}

void Buffer::bind() const
{
    glBindBuffer(static_cast<GLenum>(m_buffer_type), m_buffer_id);
}

void Buffer::bind_base(uint32_t index) const
{
    glBindBufferBase(static_cast<GLenum>(m_buffer_type), index, m_buffer_id);
}

void Buffer::update(const void *data, size_t size_bytes, int64_t offset) const
{
    glBindBuffer(static_cast<GLenum>(m_buffer_type), m_buffer_id);
    glBufferSubData(
        static_cast<GLenum>(m_buffer_type), offset, static_cast<int64_t>(size_bytes), data);
}

uint32_t Buffer::get_buffer_id() const
{
    return m_buffer_id;
}

Buffer::BUFFER_TYPE Buffer::get_buffer_type() const
{
    return m_buffer_type;
}
