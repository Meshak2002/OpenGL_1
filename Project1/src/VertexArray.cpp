#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
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

void VertexArray::AddVertexBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& vbLayout)
{
    Bind();
    vertexBuffer.Bind();
    
    unsigned int pointer=0;
    const auto& layouts = vbLayout.GetLayouts();     
    for(unsigned int i=0; i<layouts.size(); i++)
    {
        CheckGL(glEnableVertexAttribArray(layouts[i].attributeLocation));
        CheckGL(glVertexAttribPointer(layouts[i].attributeLocation,  layouts[i].components, layouts[i].dataType, layouts[i].normalized,
          vbLayout.GetStrideLength(),  (char*)(pointer))  );
        pointer += layouts[i].components*sizeof(layouts[i].dataType);
    }
}
