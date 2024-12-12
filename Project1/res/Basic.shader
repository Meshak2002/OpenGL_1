#shader vertex
#version 330 core	//glsl version
layout (location=0) in vec4 Pos; 
void main()
{ 
    gl_Position  = Pos; 
};

#shader fragment
#version 330 core
out vec4 Color;
uniform vec4 u_color;
void main() 
{ 
    Color = u_color; 
} ;