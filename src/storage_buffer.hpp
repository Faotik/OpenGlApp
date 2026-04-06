#pragma once

#include <glad/glad.h>
#include <vector>

class StorageBuffer
{
public:
    enum class DRAW_TYPE
    {
        STATIC_DRAW = GL_STATIC_DRAW,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        STREAM_DRAW = GL_STREAM_DRAW,
    };

    StorageBuffer(std::vector<float> &data, DRAW_TYPE draw_type);
    void bind(GLuint binding);
    void update(std::vector<float> &data);

public:
    GLuint m_storage_buffer;
};
