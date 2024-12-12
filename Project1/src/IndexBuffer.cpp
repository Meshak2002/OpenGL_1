#include "IndexBuffer.h"
#include "Renderer.h"
#include "GL/glew.h"


IndexBuffer::IndexBuffer(unsigned int count, unsigned int* data) : m_Count(count)
{
    Assess(sizeof(unsigned int) != sizeof(GLuint));
    CheckGL(glGenBuffers(1, &m_RendererId));
    CheckGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
    CheckGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    CheckGL(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const
{
    CheckGL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::Unbind() const
{
    CheckGL(glBindBuffer(GL_ARRAY_BUFFER,0) );
}

unsigned int IndexBuffer::GetCount() const
{
    return m_Count;
}
