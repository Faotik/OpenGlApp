#pragma once

#include <engine.hpp>
#include <glad/glad.h>
#include <span>
#include <vector>
#include <vertex_attribute_data.hpp>

class Buffer
{
public:
    enum class BUFFER_TYPE
    {
        VERTEX_BUFFER = GL_ARRAY_BUFFER,
        UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
        STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
        INDEX_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
    };

    enum class DRAW_TYPE
    {
        STATIC_DRAW = GL_STATIC_DRAW,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        STREAM_DRAW = GL_STREAM_DRAW,
    };

    Buffer(BUFFER_TYPE buffer_type, const void *data, size_t size_bytes, DRAW_TYPE draw_type);

    void bind() const;
    void bind_base(uint32_t index) const;
    void update(const void *data, size_t size_bytes, int64_t offset = 0) const;
    uint32_t get_buffer_id() const;
    BUFFER_TYPE get_buffer_type() const;

private:
    uint32_t m_buffer_id = 0;
    BUFFER_TYPE m_buffer_type;
};
