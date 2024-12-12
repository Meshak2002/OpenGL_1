#pragma once

class IndexBuffer
{
private:
    unsigned int m_RendererId;
    unsigned int m_Count;
public:
    IndexBuffer(unsigned int count, unsigned int* data);
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;
    unsigned int GetCount() const;
};