#pragma once
#include "BaseScene.h"
#include "../Common/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ayy {

class Texture2D;

namespace l7 {

struct VertexAttributePosUV
{
    float x, y, z;
    float u, v;
};

class Lesson7 : public BaseScene
{
public:
    Lesson7(int width, int height);
    virtual ~Lesson7();
    
    virtual void onEnter() override;
    virtual void onUpdate(float deltaTime) override;
    virtual void onRender() override;
    virtual void onExit() override;
    
private:
    void initVertexData();
    void initShader();
    void initTexture();
    
private:
    VertexAttributePosUV _boxVertices[36] = {
        { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f},
         {0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
         {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
         {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
        {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
        { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
        {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

        {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

         {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
         {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
         {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
         {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
         {0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
         {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
         {0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
         {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
         {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

        {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
         {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
         {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
         {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
        {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f}
    };

    unsigned int _VBO;
    unsigned int _VAO;
    
    ShaderProgram* _program = nullptr;
    
    Texture2D* _texture = nullptr;
    Texture2D* _subTexture = nullptr;
    
    float _rotDeg = 0.0f;

    // mvp matrix
    glm::mat4 _view;
    glm::mat4 _projection;
    
    // positions
    glm::vec3 _cubePositions[10] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    // 用 极坐标 确认自动移动的相机的位置
    float _camPosRadius = 10.0f;
    float _camPosRotateDeg = 0.0f;
};
}
}
