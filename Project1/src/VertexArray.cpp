#include "VertexArray.h"
#include "Renderer.h"
#include "GL/glew.h"

VertexArray::VertexArray()
{
    CheckGL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    CheckGL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind()
{
    CheckGL(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind()
{
    CheckGL(glBindVertexArray(0));
}

void VertexArray::AddVertexBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& vertexLayer)
{
    Bind();
    vertexBuffer.Bind();
    unsigned int pointer=0;
    for(int i=0; i<vertexLayer.layouts.size(); i++)
    {
        CheckGL(glEnableVertexAttribArray(i));
        CheckGL(glVertexAttribPointer(i,vertexLayer.layouts[i].components,vertexLayer.layouts[i].dataType,vertexLayer.layouts[i].normalized,
            vertexLayer.layouts[i].stride,(char*)(pointer))  );
        pointer += vertexLayer.layouts[i].components*sizeof(vertexLayer.layouts[i].dataType);
    }
}
