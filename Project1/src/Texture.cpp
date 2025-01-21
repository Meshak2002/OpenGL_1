#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"
#include <string>
#include <GL/glew.h>
#include "Renderer.h"

Texture::Texture(std::string path) : tPath(path.c_str())
{
    CheckGL(stbi_set_flip_vertically_on_load(1));
    CheckGL(data = stbi_load(tPath,&width,&height,&channels,0));
    CheckGL(glGenTextures(1,&m_RendererID));
    CheckGL(glBindTexture(GL_TEXTURE_2D,m_RendererID));
    CheckGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    CheckGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    CheckGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    CheckGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    CheckGL(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data));
    CheckGL(stbi_image_free(data));
    CheckGL(glBindTexture(GL_TEXTURE_2D,0));
}

Texture::~Texture()
{
    CheckGL(glDeleteTextures(1,&m_RendererID));
}

void Texture::Bind(unsigned int slot)
{
    CheckGL(glActiveTexture(GL_TEXTURE0 + slot));
    CheckGL(glBindTexture(GL_TEXTURE_2D,m_RendererID));
}

void Texture::Unbind()
{
    CheckGL(glBindTexture(GL_TEXTURE_2D,0));
}
