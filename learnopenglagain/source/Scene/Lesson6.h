#pragma once
#include "BaseScene.h"
#include "../Common/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ayy {

class Texture2D;

namespace l6 {

struct VertexAttributePosUV
{
    float x, y, z;
    float u, v;
};

class Lesson6 : public BaseScene
{
public:
    Lesson6(int width, int height);
    virtual ~Lesson6();
    
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
    glm::mat4 _model;
    glm::mat4 _view;
    glm::mat4 _projection;
};
}
}
