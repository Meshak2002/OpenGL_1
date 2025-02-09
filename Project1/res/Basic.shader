#shader vertex
#version 330 core	//glsl version
layout (location=0) in vec4 Pos;  
layout (location=1) in vec4 color;
layout (location=2) in vec2 texCoor;
layout (location=3) in float texSlot; 

uniform mat4 u_mvp;
out vec4 var_color;
out vec2 var_texCoor;
out float var_texSlot;

void main()
{
    var_color = color;
    var_texCoor = texCoor;
    var_texSlot = texSlot;
    gl_Position  = u_mvp * Pos; 
};
 
#shader fragment
#version 330 core
out vec4 Color;

in vec4 var_color;
in vec2 var_texCoor;
in float var_texSlot;

uniform sampler2D u_sampler[2];
uniform vec4 u_color;
uniform int u_useTexture;

void main() 
{
    int index = int(var_texSlot);
    if(u_useTexture==1)
        Color = texture(u_sampler[index],var_texCoor);
    else
        Color = vec4(index,1,1,1); 
};