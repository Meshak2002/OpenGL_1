
#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#define Assess(x) if(x) __debugbreak();
#define CheckGL(x)	 ClearGLErrors();\
x;\
Assess(IsGlError(__FILE__,#x,__LINE__))

void ClearGLErrors();

bool IsGlError(const char* file,const char* functionName,int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(Shader& shader, VertexArray& vao, IndexBuffer& ibo) const;
};
