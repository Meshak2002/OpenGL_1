
#include "Renderer.h"
#include "iostream"

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