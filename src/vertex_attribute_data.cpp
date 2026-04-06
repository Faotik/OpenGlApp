
#include "vertex_attribute_data.hpp"

VertexAttributeData::VertexAttributeData(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                         const void *pointer, GLuint location)
    : index(index), size(size), type(type), normalized(normalized), stride(stride), pointer(pointer), location(location)
{}
