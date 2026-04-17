#pragma once

#include <engine.hpp>
#include <glad/glad.h>
#include <span>

template <typename T> class StorageBuffer
{
public:
    StorageBuffer(std::span<T> data, Engine::BUFFER_DRAW_TYPE draw_type)
    {
        glGenBuffers(1, &m_buffer_id);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer_id);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
                     data.size_bytes(),
                     data.data(),
                     static_cast<GLenum>(draw_type));
    }

    StorageBuffer(int64_t size_bytes, Engine::BUFFER_DRAW_TYPE draw_type)
    {
        glGenBuffers(1, &m_buffer_id);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer_id);
        glBufferData(GL_SHADER_STORAGE_BUFFER, size_bytes, nullptr, static_cast<GLenum>(draw_type));
    }

    void bind(GLuint binding)
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, m_buffer_id);
    }

    void update(std::span<T> data, int64_t offset = 0)
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer_id);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, data.size_bytes(), data.data());
    }

private:
    GLuint m_buffer_id;
};
