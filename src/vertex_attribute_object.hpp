#pragma once

#include <buffer.hpp>
#include <glad/glad.h>
#include <span>
#include <vertex_buffer.hpp>

class VertexAttributeObject
{
public:
    VertexAttributeObject(std::span<VertexBuffer> vertex_buffers);
    VertexAttributeObject(std::span<VertexBuffer> vertex_buffers, Buffer &index_buffer);
    void bind();

private:
    GLuint m_vao_id = 0;
};