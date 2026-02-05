#pragma once
#include "BaseScene.h"
#include "../Common/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Common/Camera.h"

namespace ayy {

class Texture2D;

namespace l9 {

struct VertexAttributePos
{
    float x, y, z;
};

class Lesson9 : public BaseScene
{
public:
    Lesson9(GLFWwindow* window,int width, int height);
    virtual ~Lesson9();
    
    virtual void onEnter() override;
    virtual void onUpdate(float deltaTime) override;
    virtual void onRender() override;
    virtual void onExit() override;
    
private:
    void initVertexData();
    void initShader();
private:
    VertexAttributePos _boxVertices[36] = {
        { -0.5f, -0.5f, -0.5f,},
        {  0.5f, -0.5f, -0.5f,},
        {  0.5f,  0.5f, -0.5f,},
        {  0.5f,  0.5f, -0.5f,},
        { -0.5f,  0.5f, -0.5f,},
        { -0.5f, -0.5f, -0.5f,},

        {-0.5f, -0.5f,  0.5f,},
        {0.5f, -0.5f,  0.5f,},
        {0.5f,  0.5f,  0.5f,},
        { 0.5f,  0.5f,  0.5f,},
        {-0.5f,  0.5f,  0.5f,},
        {-0.5f, -0.5f,  0.5f,},

        {-0.5f,  0.5f,  0.5f,},
        {-0.5f,  0.5f, -0.5f,},
        {-0.5f, -0.5f, -0.5f,},
        {-0.5f, -0.5f, -0.5f,},
        {-0.5f, -0.5f,  0.5f,},
        {-0.5f,  0.5f,  0.5f,},

         {0.5f,  0.5f,  0.5f,},
         {0.5f,  0.5f, -0.5f,},
         {0.5f, -0.5f, -0.5f,},
         {0.5f, -0.5f, -0.5f,},
         {0.5f, -0.5f,  0.5f,},
         {0.5f,  0.5f,  0.5f,},

        {-0.5f, -0.5f, -0.5f,},
         {0.5f, -0.5f, -0.5f,},
         {0.5f, -0.5f,  0.5f,},
         {0.5f, -0.5f,  0.5f,},
        {-0.5f, -0.5f,  0.5f,},
        {-0.5f, -0.5f, -0.5f,},

        {-0.5f,  0.5f, -0.5f,},
         {0.5f,  0.5f, -0.5f,},
         {0.5f,  0.5f,  0.5f,},
         {0.5f,  0.5f,  0.5f,},
        {-0.5f,  0.5f,  0.5f,},
        {-0.5f,  0.5f, -0.5f,}
    };

    unsigned int _VBO;
    unsigned int _VAO;
    
    ShaderProgram* _lightShader = nullptr;
    ShaderProgram* _boxShader = nullptr;

    Camera* _camera = nullptr;
};
}
}
