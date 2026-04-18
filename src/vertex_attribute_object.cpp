#include <vertex_attribute_object.hpp>

VertexAttributeObject::VertexAttributeObject(std::span<VertexBuffer> vertex_buffers)
{
    glGenVertexArrays(1, &m_vao_id);
    glBindVertexArray(m_vao_id);

    for (const auto &vbo : vertex_buffers)
    {
        vbo.bind();
        for (const auto &attribute_data : vbo.get_attribute_data())
        {
            glVertexAttribPointer(attribute_data.index,
                                  attribute_data.size,
                                  GL_FLOAT,
                                  attribute_data.normalized,
                                  attribute_data.stride,
                                  attribute_data.pointer);
            glEnableVertexAttribArray(attribute_data.index);
            glVertexAttribDivisor(attribute_data.index, attribute_data.divisor);
        }
    }
}

VertexAttributeObject::VertexAttributeObject(std::span<VertexBuffer> vertex_buffers,
                                             Buffer &index_buffer)
{
    glGenVertexArrays(1, &m_vao_id);
    glBindVertexArray(m_vao_id);

    for (const auto &vbo : vertex_buffers)
    {
        vbo.bind();
        for (const auto &attribute_data : vbo.get_attribute_data())
        {
            glVertexAttribPointer(attribute_data.index,
                                  attribute_data.size,
                                  GL_FLOAT,
                                  attribute_data.normalized,
                                  attribute_data.stride,
                                  attribute_data.pointer);
            glEnableVertexAttribArray(attribute_data.index);
            glVertexAttribDivisor(attribute_data.index, attribute_data.divisor);
        }
    }

    index_buffer.bind();
}

void VertexAttributeObject::bind()
{
    glBindVertexArray(m_vao_id);
}