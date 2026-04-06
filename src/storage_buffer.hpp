#pragma once

#include <glad/glad.h>
#include <vector>

template <typename T> class StorageBuffer
{
public:
    enum class DRAW_TYPE
    {
        STATIC_DRAW = GL_STATIC_DRAW,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        STREAM_DRAW = GL_STREAM_DRAW,
    };

    StorageBuffer(const std::vector<T> &data, DRAW_TYPE draw_type)
    {
        glGenBuffers(1, &m_storage_buffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_storage_buffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(), static_cast<GLenum>(draw_type));
    }

    void bind(GLuint binding)
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, m_storage_buffer);
    }

    void update(const std::vector<T> &data)
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_storage_buffer);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data.size() * sizeof(T), data.data());
    }

public:
    GLuint m_storage_buffer;
};
