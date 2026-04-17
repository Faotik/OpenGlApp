#pragma once

#include <glad/glad.h>

class VertexAttributeData
{
public:
    VertexAttributeData(GLuint index,
                        GLint size,
                        GLboolean normalized,
                        GLsizei stride,
                        const void *pointer,
                        GLuint divisor = 0);

public:
    const GLuint index;
    const GLint size;
    const GLboolean normalized;
    const GLsizei stride;
    const void *pointer;
    const GLuint divisor;
};