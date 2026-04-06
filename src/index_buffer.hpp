#pragma once

#include <glad/glad.h>
#include <vector>

class IndexBuffer
{
public:
    enum class DRAW_TYPE
    {
        STATIC_DRAW = GL_STATIC_DRAW,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        STREAM_DRAW = GL_STREAM_DRAW,
    };

    IndexBuffer(std::vector<int> &data, DRAW_TYPE draw_type);

public:
    GLuint m_index_buffer;
};
