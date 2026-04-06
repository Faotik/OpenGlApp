
#include <glad/glad.h>

class VertexAttributeData
{
public:
    VertexAttributeData(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer,
                        GLuint location);

public:
    const GLuint index;
    const GLint size;
    const GLenum type;
    const GLboolean normalized;
    const GLsizei stride;
    const void *pointer;
    const GLuint location;
};