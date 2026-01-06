#pragma once
#include <iostream>

namespace ayy
{
class Texture2D
{
public:
    Texture2D();
    ~Texture2D();
    void load(const std::string& filePath);
    
    unsigned int getTextureHandle() const { return _texture;}
    
private:
    int _width;
    int _height;
    int _channels;
    
    unsigned int _texture = 0;
};
}
