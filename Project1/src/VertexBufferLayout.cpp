#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() :     m_stride(0)
{}

template<typename T>
void VertexBufferLayout::AssignLayoutElement(unsigned int components,EAttributeType attributeType,GLboolean normalized)
{
    static_assert(true, "Vertex Buffer Layout is not supported"); 
}

template<>
void VertexBufferLayout::AssignLayoutElement<float>(unsigned int components,EAttributeType attributeType,GLboolean normalized)
{
    LayoutAttribute attribute{components,GL_FLOAT,attributeType,normalized};
    m_stride += components*attribute.GetSizeOf(GL_FLOAT);
    layouts.push_back(attribute);
}

template<>
void VertexBufferLayout::AssignLayoutElement<unsigned int>(unsigned int components,EAttributeType attributeType,GLboolean normalized)
{
    LayoutAttribute attribute{components,GL_UNSIGNED_INT,attributeType,normalized};
    m_stride += components*attribute.GetSizeOf(GL_UNSIGNED_INT);
    layouts.push_back(attribute);
}

template<>
void VertexBufferLayout::AssignLayoutElement<unsigned char>(unsigned int components,EAttributeType attributeType,GLboolean normalized)
{
    LayoutAttribute attribute{components,GL_UNSIGNED_BYTE,attributeType,normalized};
    m_stride += components*attribute.GetSizeOf(GL_UNSIGNED_BYTE);
    layouts.push_back(attribute);
}

std::vector<LayoutAttribute> VertexBufferLayout::GetLayouts() const
{
    return layouts;
}

unsigned int VertexBufferLayout::GetStrideLength() const
{
    return m_stride;
}


