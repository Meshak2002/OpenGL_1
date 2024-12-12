#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{
}
VertexBufferLayout::~VertexBufferLayout()
{ 
}

template<typename T>
void VertexBufferLayout::AssignLayoutElement(unsigned int components,GLboolean normalized)
{
    static_assert(true, "Vertex Buffer Layout is not supported"); 
}

template<>
void VertexBufferLayout::AssignLayoutElement<float>(unsigned int components,GLboolean normalized)
{
    GLsizei stride = components*sizeof(float);
    LayoutAttributes attribute{components,GL_FLOAT,normalized,stride};
    layouts.push_back(attribute);
}

template<>
void VertexBufferLayout::AssignLayoutElement<unsigned int>(unsigned int components,GLboolean normalized)
{
    GLsizei stride = components*sizeof(int);
    LayoutAttributes attribute{components,GL_UNSIGNED_INT,normalized,stride};
    layouts.push_back(attribute);
}
