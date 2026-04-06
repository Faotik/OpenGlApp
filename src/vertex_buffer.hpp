#pragma once

#include "vertex_attribute_data.hpp"
#include <glad/glad.h>
#include <vector>

class VertexBuffer
{
public:
    enum class DRAW_TYPE
    {
        STATIC_DRAW = GL_STATIC_DRAW,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        STREAM_DRAW = GL_STREAM_DRAW,
    };

    VertexBuffer(const std::vector<float> &data, DRAW_TYPE draw_type, const std::vector<VertexAttributeData> attribute_data);

public:
    GLuint m_vertex_buffer;
    std::vector<VertexAttributeData> m_attribute_data;
};
