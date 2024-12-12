
#pragma once
#include "GL/glew.h"

#define Assess(x) if(x) __debugbreak();
#define CheckGL(x)	 ClearGLErrors();\
x;\
Assess(IsGlError(__FILE__,#x,__LINE__))

void ClearGLErrors();

bool IsGlError(const char* file,const char* functionName,int line);
