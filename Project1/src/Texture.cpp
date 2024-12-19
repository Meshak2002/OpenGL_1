#include "Texture.h"

#include <string>
#include <GL/glew.h>

#include "vendor/stb_image.h"

Texture::Texture(std::string path) : tPath(path.c_str())
{
    stbi_set_flip_vertically_on_load(1);
    data = stbi_load(tPath,&width,&height,&channels,0);
    glGenTextures(1,&m_RendererID);
    glBindTexture(GL_TEXTURE_2D,m_RendererID);
    glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1,&m_RendererID);
}

void Texture::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D,m_RendererID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}
