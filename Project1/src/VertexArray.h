#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();
    void Bind();
    void Unbind();
    void AddVertexBuffer(VertexBuffer& vertexBuffer,VertexBufferLayout& vertexLayer);
private:
    unsigned int m_RendererID;
    
};
