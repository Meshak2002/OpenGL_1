#pragma once
#include <xstring>

class Texture
{
public:
    Texture(std::string path);
    ~Texture();
    void Bind(unsigned int slot = 0);
    void Unbind();
private:
    unsigned int m_RendererID;
    unsigned char* data;
    const char* tPath;
    int width, height , channels;
};
