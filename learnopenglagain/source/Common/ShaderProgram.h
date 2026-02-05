#pragma once
#include <string>
#include <glm/glm.hpp>

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

    void setInt(const std::string& propName,int value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    unsigned int _vertexShader;
    unsigned int _fragmentShader;
    unsigned int _program;
    
    std::string _vertexSource;
    std::string _fragmentSource;
    
};

}
