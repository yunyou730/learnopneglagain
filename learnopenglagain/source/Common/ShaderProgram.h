#pragma once
#include <string>

namespace ayy
{

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertexSource,const std::string& fragmentSource);
    ~ShaderProgram();
    
    bool compileLink();
    void useProgram();
    
    unsigned int getProgram() const { return _program;}

    void setInt(const std::string& propName,int value);
    
private:
    unsigned int _vertexShader;
    unsigned int _fragmentShader;
    unsigned int _program;
    
    std::string _vertexSource;
    std::string _fragmentSource;
    
};

}
