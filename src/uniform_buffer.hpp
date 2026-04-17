#pragma once

#include <engine.hpp>
#include <glad/glad.h>
#include <span>

template <typename T> class UniformBuffer
{
public:
    UniformBuffer(std::span<T> data, Engine::BUFFER_DRAW_TYPE draw_type)
    {
        glGenBuffers(1, &m_buffer_id);
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        glBufferData(
            GL_UNIFORM_BUFFER, data.size_bytes(), data.data(), static_cast<GLenum>(draw_type));
    }

    UniformBuffer(T data, Engine::BUFFER_DRAW_TYPE draw_type)
    {
        glGenBuffers(1, &m_buffer_id);
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(data), &data, static_cast<GLenum>(draw_type));
    }

    UniformBuffer(int64_t size_bytes, Engine::BUFFER_DRAW_TYPE draw_type)
    {
        glGenBuffers(1, &m_buffer_id);
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        glBufferData(GL_UNIFORM_BUFFER, size_bytes, nullptr, static_cast<GLenum>(draw_type));
    }

    void bind(GLuint binding)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_buffer_id);
    }

    void update(std::span<T> data, int64_t offset = 0)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, data.size_bytes(), data.data());
    }

    void update(T data, int64_t offset = 0)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_buffer_id);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(data), &data);
    }

private:
    GLuint m_buffer_id;
};
