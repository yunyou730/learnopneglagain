#pragma once
#include <iostream>

namespace ayy {

class ShaderFileReader
{
public:
    static std::string readShaderCode(const std::string& filePath);
};

}
