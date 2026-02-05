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

    void drawBox();
    void drawLight();
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

    unsigned int _boxVAO;
    unsigned int _lightVAO;
    
    ShaderProgram* _lightShader = nullptr;
    ShaderProgram* _boxShader = nullptr;

    Camera* _camera = nullptr;

	glm::vec3 _lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    glm::vec3 _lightColor = glm::vec3(1.0,0.7,1.0);
};
}
}
