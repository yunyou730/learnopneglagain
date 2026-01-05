#include "ShaderProgram.h"
#include <glad/glad.h>
#include <iostream>

namespace ayy
{

ShaderProgram::ShaderProgram(const std::string& vertexSource,const std::string& fragmentSource)
{
    _vertexSource = vertexSource;
    _fragmentSource = fragmentSource;
}

ShaderProgram::~ShaderProgram()
{

}

bool ShaderProgram::compileLink()
{
    // vertex shader
    _vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vcode = _vertexSource.c_str();
    glShaderSource(_vertexShader,1,&vcode,NULL);
    glCompileShader(_vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(_vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    
    // fragment shader
    const char* fcode = _fragmentSource.c_str();
    _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragmentShader,1,&fcode,NULL);
    glCompileShader(_fragmentShader);
    glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(_fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    
    // link program
    _program = glCreateProgram();
    glAttachShader(_program,_vertexShader);
    glAttachShader(_program,_fragmentShader);
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        return false;
    }
    
    // delete vertex shader,fragment shader
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);

    // all success
    return true;
}

void ShaderProgram::useProgram()
{
    glUseProgram(_program);
}

}

