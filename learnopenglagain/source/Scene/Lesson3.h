#pragma once
#include "BaseScene.h"
#include "../Common/ShaderProgram.h"

namespace ayy {

class Texture2D;

namespace lesson3 {
struct VertexAttribute
{
    float x,y,z;
    float r,g,b;
    float u,v;
};

class Lesson3 : public BaseScene
{
public:
    Lesson3(int width, int height);
    virtual ~Lesson3();
    
    virtual void onEnter() override;
    virtual void onUpdate(float deltaTime) override;
    virtual void onRender() override;
    virtual void onExit() override;
    
private:
    void initVertexData();
    void initShader();
    void initTexture();
    
private:
    VertexAttribute _vertices[4] = {
        {0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0,1.0}, // 第1个顶点：右上角 + 红色 + uv
        {0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0,0.0}, // 第2个顶点：右下角 + 绿色 + uv
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0,0.0}, // 第3个顶点：左下角 + 蓝色 + uv
        {-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0,1.0}  // 第4个顶点：左上角 + 黄色 + uv
    };
    
    unsigned int _indices[6] = {
        0,1,3,  // 第一个三角形
        1,2,3   // 第二个三角形
    };
    
    unsigned int _VBO;
    unsigned int _VAO;
    unsigned int _EBO;
    
    ShaderProgram* _program = nullptr;
    
    
    Texture2D* _texture = nullptr;
};
}
}
