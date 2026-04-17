
#include <vertex_attribute_data.hpp>

VertexAttributeData::VertexAttributeData(GLuint index,
                                         GLint size,
                                         GLboolean normalized,
                                         GLsizei stride,
                                         const void *pointer,
                                         GLuint divisor)
    : index(index), size(size), normalized(normalized), stride(stride), pointer(pointer),
      divisor(divisor)
{}
