#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();
    void Bind();
    void Unbind();
    void AddVertexBuffer(VertexBuffer& vertexBuffer,VertexBufferLayout& vbLayout);
private:
    unsigned int m_RendererID;
    
};
