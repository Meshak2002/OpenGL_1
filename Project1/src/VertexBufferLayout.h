#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct LayoutAttribute
{
    unsigned int components;
    GLenum dataType;
    GLboolean normalized;

    unsigned int GetSizeOf(unsigned int dataType)
    {
        switch (dataType)
        {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            case GL_INT:
                return 4;
        }
        Assess(true);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    unsigned int m_stride;
    std::vector<LayoutAttribute> layouts;
public:
    VertexBufferLayout();
    template<typename T>
    void AssignLayoutElement(unsigned int components,GLboolean normalized);

    std::vector<LayoutAttribute> GetLayouts() const;
    unsigned int GetStrideLength() const;
};

