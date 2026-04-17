

#include <vertex_attribute_object.hpp>

VertexAttributeObject::VertexAttributeObject(std::span<VertexBuffer> vertex_buffers)
{
    glGenVertexArrays(1, &m_vao_id);
    glBindVertexArray(m_vao_id);

    for (const auto &vbo : vertex_buffers)
    {
        vbo.bind();
        for (const auto &attribute_data : vbo.m_attribute_data)
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
                                             IndexBuffer &index_buffer)
{
    glGenVertexArrays(1, &m_vao_id);
    glBindVertexArray(m_vao_id);

    for (const auto &vbo : vertex_buffers)
    {
        vbo.bind();
        for (const auto &attribute_data : vbo.m_attribute_data)
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.m_index_buffer);
}

void VertexAttributeObject::bind()
{
    glBindVertexArray(m_vao_id);
}