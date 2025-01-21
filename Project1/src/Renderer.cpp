
#include "Renderer.h"
#include "iostream"
#include "GL/glew.h"

void ClearGLErrors()
{
    while (glGetError() != GL_NO_ERROR);
}
bool IsGlError(const char* file,const char* functionName,int line)
{
    bool error = false;
    while(GLenum glError = glGetError())
    {
        std::cout<<"OpenGL Error: ox"<< std::hex <<file<<functionName<<line<<glError<<std::endl;
        error = true;
    }
    return error;
}

void Renderer::Clear() const
{
    CheckGL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(Shader& shader, VertexArray& vao, IndexBuffer& ibo) const
{
    shader.bind();
    vao.Bind();
    ibo.Bind();
    CheckGL(glDrawElements(GL_TRIANGLES,ibo.GetCount(),GL_UNSIGNED_INT,nullptr));

}

