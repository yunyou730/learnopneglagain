#include "ShaderFileReader.h"
#include <fstream>
#include <sstream>

namespace ayy
{
std::string ShaderFileReader::readShaderCode(const std::string& filePath)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch(std::ifstream::failure ex)
    {
        std::cout << "ERROR:SHADER::FILE_NOT_SUCCESFULLY_READ:" << filePath << std::endl;
    }
    return shaderCode;
}
}


