#pragma once

class VertexBuffer
{
private:
    unsigned int m_RendererId;

public:
    VertexBuffer(unsigned int size, void* data);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
    
};