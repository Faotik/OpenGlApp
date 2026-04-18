#pragma once
#include <buffer.hpp>

class VertexBuffer
{
public:
    VertexBuffer(const void *data,
                 size_t size_bytes,
                 Buffer::DRAW_TYPE draw_type,
                 std::vector<VertexAttributeData> attribute_data);
    void bind() const;
    void update(const void *data, size_t size_bytes, int64_t offset = 0) const;
    std::span<const VertexAttributeData> get_attribute_data() const;

private:
    Buffer m_buffer;
    std::vector<VertexAttributeData> m_attribute_data;
};
