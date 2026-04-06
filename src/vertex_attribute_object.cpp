
#include "vertex_attribute_object.hpp"
#include "vertex_buffer.hpp"
#include <vector>

VertexAttributeObject::VertexAttributeObject(std::vector<VertexBuffer> &vertex_buffers)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    for (const auto &vbo : vertex_buffers)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo.m_vertex_buffer);
        for (const auto &attribute_data : vbo.m_attribute_data)
        {
            glVertexAttribPointer(attribute_data.index, attribute_data.size, attribute_data.type, attribute_data.normalized,
                                  attribute_data.stride, attribute_data.pointer);
            glEnableVertexAttribArray(attribute_data.location);
        }
    }
}

VertexAttributeObject::VertexAttributeObject(std::vector<VertexBuffer> &vertex_buffers, IndexBuffer &index_buffer)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    for (const auto &vbo : vertex_buffers)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo.m_vertex_buffer);
        for (const auto &attribute_data : vbo.m_attribute_data)
        {
            glVertexAttribPointer(attribute_data.index, attribute_data.size, attribute_data.type, attribute_data.normalized,
                                  attribute_data.stride, attribute_data.pointer);
            glEnableVertexAttribArray(attribute_data.location);
        }
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.m_index_buffer);
}

VertexAttributeObject::VertexAttributeObject(VertexBuffer &vertex_buffer)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer.m_vertex_buffer);
    for (const auto &attribute_data : vertex_buffer.m_attribute_data)
    {
        glVertexAttribPointer(attribute_data.index, attribute_data.size, attribute_data.type, attribute_data.normalized,
                              attribute_data.stride, attribute_data.pointer);
        glEnableVertexAttribArray(attribute_data.location);
    }
}

VertexAttributeObject::VertexAttributeObject(VertexBuffer &vertex_buffer, IndexBuffer &index_buffer)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer.m_vertex_buffer);
    for (const auto &attribute_data : vertex_buffer.m_attribute_data)
    {
        glVertexAttribPointer(attribute_data.index, attribute_data.size, attribute_data.type, attribute_data.normalized,
                              attribute_data.stride, attribute_data.pointer);
        glEnableVertexAttribArray(attribute_data.location);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.m_index_buffer);
}

void VertexAttributeObject::bind()
{
    glBindVertexArray(m_vao);
}