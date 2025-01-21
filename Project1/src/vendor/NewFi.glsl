#shader vertex
#version 330 core	//glsl version
layout (location=0) in vec4 Pos;  
layout (location=1) in vec2 texCoor;

uniform mat4 u_mvp;
out vec2 var_texCoor;

void main()
{
    var_texCoor = texCoor;
    gl_Position  = Pos*u_mvp; 
};
 
#shader fragment
#version 330 core
out vec4 Color;
in vec2 var_texCoor;

uniform sampler2D u_sampler;
uniform vec4 u_color;

void main() 
{
    vec4 texColor = texture(u_sampler,var_texCoor);  
    Color = texColor; 
} ;