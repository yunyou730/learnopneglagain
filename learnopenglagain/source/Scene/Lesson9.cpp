#include "Lesson9.h"
#include <glad/glad.h>
#include "../Common/ShaderFileReader.h"
#include "../Common/Texture2D.h"
#include <GLFW/glfw3.h>

namespace ayy {
namespace l9 {

Lesson9::Lesson9(GLFWwindow* window,int width, int height)
	:BaseScene(window,width, height)
{
    _camera = new Camera();
}

Lesson9::~Lesson9()
{
    delete _lightShader;
    _lightShader = nullptr;

    delete _boxShader;
    _boxShader = nullptr;

    glDeleteVertexArrays(1,&_boxVAO);
    glDeleteVertexArrays(1, &_lightVAO);
    glDeleteBuffers(1,&_VBO);

    delete _camera;
    _camera = nullptr;
}

void Lesson9::onEnter()
{
    glClearColor(0.1,0.1,0.1,1.0);
    initShader();
    initVertexData();
}

void Lesson9::initVertexData()
{
    // Box VAO
    glGenVertexArrays(1, &_boxVAO); 
    glGenBuffers(1, &_VBO);     // // vertex data
    glBindVertexArray(_boxVAO);
    {
        // 1. bind VAO
        glBindVertexArray(_boxVAO);
        // 2. bind VBO, fill buffer data
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_boxVertices), _boxVertices, GL_STATIC_DRAW);
        
        // 3. Set Vertex attribute for binding VBO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
            sizeof(VertexAttributePos),
            (void*)offsetof(VertexAttributePos, x)); // 位置属性
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
            sizeof(VertexAttributePos),
            (void*)offsetof(VertexAttributePos,nx));    // 法线属性

        // 4. 开启 顶点属性
        glEnableVertexAttribArray(0);   // 开启 位置属性
		glEnableVertexAttribArray(1);   // 开启 法线属性
    }
    glBindVertexArray(0);

	// Light VAO.  和 Box VAO 共用同样的 VBO
    glGenVertexArrays(1, &_lightVAO);
    glBindVertexArray(_lightVAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
            sizeof(VertexAttributePos),
            (void*)offsetof(VertexAttributePos, x)); // 位置属性
        glEnableVertexAttribArray(0);               // 开启 位置属性
    }
    glBindVertexArray(0);
}

void Lesson9::initShader()
{
    std::string vertShaderCode = ShaderFileReader::readShaderCode("res/lesson9/lit_object_vert.glsl");
    std::string fragShaderCode = ShaderFileReader::readShaderCode("res/lesson9/lit_object_frag.glsl");
    _boxShader = new ShaderProgram(vertShaderCode, fragShaderCode);
    _boxShader->compileLink();

    vertShaderCode = ShaderFileReader::readShaderCode("res/lesson9/light_vert.glsl");
    fragShaderCode = ShaderFileReader::readShaderCode("res/lesson9/light_frag.glsl");
    _lightShader = new ShaderProgram(vertShaderCode, fragShaderCode);
    _lightShader->compileLink();
}

void Lesson9::onUpdate(float deltaTime)
{
    _camera->updateMatrix(_windowWidth, _windowHeight);
    _camera->updateControl(getWindow(), deltaTime);
}

void Lesson9::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    drawBox();
    drawLight();
}

void Lesson9::drawBox()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    _boxShader->useProgram();
    _boxShader->setMat4("u_Model", model);
    _boxShader->setMat4("u_View", _camera->getViewMatrix());
    _boxShader->setMat4("u_Projection", _camera->getProjectionMatrix());
    _boxShader->setVec3("u_ObjectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    _boxShader->setVec3("u_LightColor", _lightColor);
    _boxShader->setVec3("u_LightPos",_lightPos);
    glBindVertexArray(_boxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Lesson9::drawLight()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _lightPos);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

    _lightShader->useProgram();
    _lightShader->setMat4("u_Model", model);
    _lightShader->setMat4("u_View", _camera->getViewMatrix());
    _lightShader->setMat4("u_Projection", _camera->getProjectionMatrix());
    _lightShader->setVec3("u_LightColor", _lightColor);
    glBindVertexArray(_lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Lesson9::onExit()
{
    
}
}
}
