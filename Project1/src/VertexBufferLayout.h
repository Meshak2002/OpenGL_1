#pragma once
#include <vector>
#include <GL/glew.h>

struct LayoutAttributes
{
    unsigned int components;
    GLenum dataType;
    GLboolean normalized;
    GLsizei stride;
};

class VertexBufferLayout
{
    public:
    VertexBufferLayout();
    ~VertexBufferLayout();
    
    template<typename T>
    void AssignLayoutElement(unsigned int components,GLboolean normalized);
    std::vector<LayoutAttributes> layouts;
};

