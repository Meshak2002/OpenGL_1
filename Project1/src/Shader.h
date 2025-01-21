#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include <glm/fwd.hpp>

struct ShaderSrc
{
    std::string vertexSource;
    std::string fragmentSource;
};
enum class ShaderType
{
    NONE=-1,
    VERTEX=0,
    FRAGMENT=1
};

class Shader
{
public:
    Shader(std::string filePath);
    ~Shader();
    void bind();
    void unbind();
    void SetUniform4f(std::string name, float x, float y, float z, float w);
    void SetUniform1f(std::string name, float x);
    void SetUniformMatrix(const std::string& name, glm::mat4& matrix);
private:
    unsigned int m_renderId;
    std::string m_filePath;
    std::unordered_map<std::string, int> m_uniformLocationCache;
    ShaderSrc ParseShaders(std::string directory);
    unsigned int CompileShader(unsigned int type, std::string source);
    unsigned int CreateShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
    int GetUniformLoc(std::string name);
    
};


