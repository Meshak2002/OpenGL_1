#include "VertexBuffer.h"
#include "Renderer.h"
#include "GL/glew.h"

VertexBuffer::VertexBuffer(unsigned int size, void* data)
{
    CheckGL(glGenBuffers(1, &m_RendererId));
    CheckGL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    CheckGL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    CheckGL(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const
{
    CheckGL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::Unbind() const
{
    CheckGL(glBindBuffer(GL_ARRAY_BUFFER,0) );
}
