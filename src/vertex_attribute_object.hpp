#pragma once

#include <glad/glad.h>
#include <index_buffer.hpp>
#include <span>
#include <vertex_buffer.hpp>

class VertexAttributeObject
{
public:
    VertexAttributeObject(std::span<VertexBuffer> vertex_buffers);
    VertexAttributeObject(std::span<VertexBuffer> vertex_buffers, IndexBuffer &index_buffer);
    void bind();

private:
    GLuint m_vao_id;
};