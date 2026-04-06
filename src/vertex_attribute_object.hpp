#pragma once

#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include <glad/glad.h>
#include <vector>

class VertexAttributeObject
{
public:
    VertexAttributeObject(std::vector<VertexBuffer> &vertex_buffers);
    VertexAttributeObject(std::vector<VertexBuffer> &vertex_buffers, IndexBuffer &index_buffer);
    VertexAttributeObject(VertexBuffer &vertex_buffer);
    VertexAttributeObject(VertexBuffer &vertex_buffer, IndexBuffer &index_buffer);
    void bind();

public:
    GLuint m_vao;
};