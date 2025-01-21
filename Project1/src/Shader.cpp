#include "Shader.h"
#include "Renderer.h"
#include "fstream"
#include "sstream"
#include "iostream"
#include "GL/glew.h"

Shader::Shader(std::string filePath) : m_filePath(filePath)
{
    ShaderSrc shaders = ParseShaders(filePath);
    m_renderId = CreateShaderProgram(shaders.vertexSource,shaders.fragmentSource);
}

Shader::~Shader()
{
    CheckGL(glDeleteProgram(m_renderId));
}

void Shader::bind()
{
    CheckGL(glUseProgram(m_renderId));
}

void Shader::unbind()
{
    CheckGL(glUseProgram(0));
}

ShaderSrc Shader::ParseShaders(std::string directory)
{
    ShaderType type = ShaderType::NONE;
    std::ifstream file(directory);
    std::string line;
    std::stringstream ss[2];
    while(getline(file, line))
    {
        if(line.find("#shader")!=std::string::npos)
        {
            if(line.find("vertex")!=std::string::npos)
                type = ShaderType::VERTEX;
            if(line.find("fragment")!=std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
            ss[(int)type]<<line<<std::endl;
    }
    return {ss[0].str(),ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, std::string source)
{
    unsigned int shader=glCreateShader(type);
    const char* srcStart = source.c_str(); //Returns the address of first character in the string
    glShaderSource(shader,1,&srcStart,NULL);
    glCompileShader(shader);
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)		//result == 0
    {
        int length;
        glGetShaderiv(shader,GL_INFO_LOG_LENGTH, &length);
        char* logMessage= (char*) alloca((sizeof(char) * length));
        glGetShaderInfoLog(shader,length,&length,logMessage);
        std::cout <<"Failed To comile "<<( (type==GL_VERTEX_SHADER)?"Vertex Shader":"Fragment Shader")<<" sad"<< std::endl;
        std::cout << logMessage<<std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

unsigned int Shader::CreateShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource)
{
    unsigned int programm= glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int FragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    glAttachShader(programm, vertexShader);
    glAttachShader(programm, FragmentShader);
    glLinkProgram(programm);
    glValidateProgram(programm);
    glDeleteShader(vertexShader);
    glDeleteShader(FragmentShader);
    return programm;
}

void Shader::SetUniform4f(std::string name, float x, float y, float z, float w)
{
    glUniform4f(   GetUniformLoc(name)   ,x,y,z,w);
}

void Shader::SetUniform1f(std::string name, float x)
{
    glUniform1f( GetUniformLoc(name)   ,x);
}

void Shader::SetUniformMatrix(const std::string& name, glm::mat4& matrix)
{
   CheckGL( glUniformMatrix4fv(GetUniformLoc(name),1,GL_FALSE,&matrix[0][0]) );
}

int Shader::GetUniformLoc(std::string name)
{
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];
    int shaderColorVar = glGetUniformLocation(m_renderId, &name[0]);
    if(shaderColorVar == -1)
        std::cout<<"Failed to get uniform location!"<<std::endl;
    m_uniformLocationCache[name] = shaderColorVar;
    return shaderColorVar;
}
