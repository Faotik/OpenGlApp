#pragma once

#include <engine.hpp>
#include <glad/glad.h>
#include <span>
#include <vector>
#include <vertex_attribute_data.hpp>

class VertexBuffer
{
public:
    VertexBuffer(std::span<float> data,
                 Engine::BUFFER_DRAW_TYPE draw_type,
                 std::vector<VertexAttributeData> attribute_data);

    VertexBuffer(int64_t size_bytes,
                 Engine::BUFFER_DRAW_TYPE draw_type,
                 std::vector<VertexAttributeData> attribute_data);

    void bind() const;

    void update(std::span<float> data, int64_t offset = 0);

public:
    std::vector<VertexAttributeData> m_attribute_data;

private:
    GLuint m_buffer_id;
};
