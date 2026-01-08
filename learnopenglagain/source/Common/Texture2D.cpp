#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

namespace ayy {

Texture2D::Texture2D()
{
    
}

Texture2D::~Texture2D()
{
    if(_texture > 0)
    {
        glDeleteTextures(1,&_texture);
        _texture = 0;
    }
}

void Texture2D::load(const std::string& filePath)
{
    glGenTextures(1,&_texture);
    glBindTexture(GL_TEXTURE_2D,_texture);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    unsigned char* data = stbi_load(filePath.c_str(),&_width,&_height,&_channels,0);
    if(data != nullptr && (_channels == 3 || _channels == 4))
    {
        if (_channels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (_channels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture:" << filePath << ",channels:" << _channels << std::endl;
    }
    
    glBindTexture(GL_TEXTURE_2D,0);
}

}
