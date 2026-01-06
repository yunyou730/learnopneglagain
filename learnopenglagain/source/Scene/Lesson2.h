#pragma once
#include "BaseScene.h"
#include "../Common/ShaderProgram.h"

namespace ayy {
namespace lesson2 {
struct VertexAttribute
{
    float x,y,z;
    float r,g,b;
};

class Lesson2 : public BaseScene
{
public:
    Lesson2();
    virtual ~Lesson2();
    
    virtual void onEnter() override;
    virtual void onUpdate(float deltaTime) override;
    virtual void onRender() override;
    virtual void onExit() override;
    
private:
    VertexAttribute _vertices[4] = {
        {0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f}, // 第1个顶点：右上角 + 红色
        {0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f}, // 第2个顶点：右下角 + 绿色
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f}, // 第3个顶点：左下角 + 蓝色
        {-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f}  // 第4个顶点：左上角 + 黄色
    };
    
    unsigned int _indices[6] = {
        0,1,3,  // 第一个三角形
        1,2,3   // 第二个三角形
    };
    
    unsigned int _VBO;
    unsigned int _VAO;
    unsigned int _EBO;
    
    ShaderProgram* _program = nullptr;
};
}
}
