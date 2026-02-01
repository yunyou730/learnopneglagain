#include "Lesson8.h"
#include <glad/glad.h>
#include "../Common/ShaderFileReader.h"
#include "../Common/Texture2D.h"
#include <GLFW/glfw3.h>

namespace ayy {
namespace l8 {

Lesson8::Lesson8(GLFWwindow* window,int width, int height)
	:BaseScene(window,width, height)
{

}

Lesson8::~Lesson8()
{
    delete _program;
    _program = nullptr;
    
    glDeleteVertexArrays(1,&_VAO);
    glDeleteBuffers(1,&_VBO);

    delete _texture;
    _texture = nullptr;

    delete _subTexture;
	_subTexture = nullptr;
}


void Lesson8::onEnter()
{
    glClearColor(0.5,0.8,0.2,1.0);

    initShader();
    initVertexData();
    initTexture();

	_projection = glm::perspective(glm::radians(45.0f), (float)_windowWidth / (float)_windowHeight, 0.1f, 100.0f);
}

void Lesson8::initVertexData()
{
    // vertex data
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    //glGenBuffers(1, &_EBO);

    // 1. bind VAO
    glBindVertexArray(_VAO);
    // 2. bind VBO, fill buffer data
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_boxVertices), _boxVertices, GL_STATIC_DRAW);

    // 4. Set Vertex attribute for binding VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(VertexAttributePosUV),
        (void*)offsetof(VertexAttributePosUV, x)); // 位置属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
        sizeof(VertexAttributePosUV),
        (void*)offsetof(VertexAttributePosUV, u));// uv

    glEnableVertexAttribArray(0);   // 开启 位置属性
    glEnableVertexAttribArray(1);   // 开启 UV
}

void Lesson8::initShader()
{
    std::string vertShaderCode = ShaderFileReader::readShaderCode("res/lesson7/vert.glsl");
    std::string fragShaderCode = ShaderFileReader::readShaderCode("res/lesson7/frag.glsl");
    _program = new ShaderProgram(vertShaderCode, fragShaderCode);
    _program->compileLink();
}

void Lesson8::initTexture()
{
    _texture = new Texture2D();
    _texture->load("res/common/container.jpg");

    _subTexture = new Texture2D();
    _subTexture->load("res/common/awesomeface.png");
}


void Lesson8::onUpdate(float deltaTime)
{
    // update object rotation
    _rotDeg += deltaTime * 35.0f;
    
    // update camera control
    updateCameraControl(deltaTime);

    // refresh matrix
    _projection = glm::perspective(glm::radians(45.0f), (float)_windowWidth / (float)_windowHeight, 0.1f, 100.0f);
    _view = glm::lookAt(_cameraPos,_cameraPos + _cameraFront,_cameraUp);
}


void Lesson8::updateCameraControl(float deltaTime)
{
    float moveOffset = _cameraMoveSpeed * deltaTime;
    float rotateOffset = _cameraRotateSpeed * deltaTime;

    if (glfwGetKey(getWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        _cameraPos += moveOffset * _cameraFront;
    }
    if (glfwGetKey(getWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        _cameraPos -= moveOffset * _cameraFront;
    }
    if (glfwGetKey(getWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        _cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * moveOffset;
    }
    if (glfwGetKey(getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        _cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * moveOffset;
    }
    if (glfwGetKey(getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        // 向左转
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat,glm::radians(rotateOffset),_cameraUp);
        
        glm::vec4 front;
        front.x = _cameraFront.x;
        front.y = _cameraFront.y;
        front.z = _cameraFront.z;
        front.w = 0.0f;
        front = mat * front;
        _cameraFront = front;
    }
    if (glfwGetKey(getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        // 向右转
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat,glm::radians(-rotateOffset),_cameraUp);
        
        glm::vec4 front;
        front.x = _cameraFront.x;
        front.y = _cameraFront.y;
        front.z = _cameraFront.z;
        front.w = 0.0f;
        front = mat * front;
        _cameraFront = front;
    }
    if (glfwGetKey(getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        glm::vec3 right = glm::normalize(glm::cross(_cameraFront, _cameraUp));
        
        // 仰头
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat,glm::radians(rotateOffset),right);
        
        glm::vec4 front;
        front.x = _cameraFront.x;
        front.y = _cameraFront.y;
        front.z = _cameraFront.z;
        front.w = 0.0f;
        front = mat * front;
        _cameraFront = front;
    }
    if (glfwGetKey(getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        // 低头
        glm::vec3 right = glm::normalize(glm::cross(_cameraFront, _cameraUp));
        
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat,glm::radians(-rotateOffset),right);
        
        glm::vec4 front;
        front.x = _cameraFront.x;
        front.y = _cameraFront.y;
        front.z = _cameraFront.z;
        front.w = 0.0f;
        front = mat * front;
        _cameraFront = front;
    }

}

void Lesson8::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);   // texture unit 0
    glBindTexture(GL_TEXTURE_2D, _texture->getTextureHandle());     // bind texture unit 0 with texture handle

	glActiveTexture(GL_TEXTURE1);   // texture unit 1
    glBindTexture(GL_TEXTURE_2D, _subTexture->getTextureHandle());  // bind texture unit 1 with texture handle

    _program->useProgram();
	_program->setInt("u_MainTex", 0);   // bind texture unit 0 to shader uniform
    _program->setInt("u_SecondTex", 1); // bind texture unit 1 to shader uniform
    
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);

    for (int i = 0;i < 10;i++)
    {
        // 缩放 + 平移
		glm::mat4 model(1.0f);
		model = glm::translate(model, _cubePositions[i]);
        float angle = _rotDeg * (i + 1);
        model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));

        // MVP 矩阵
        unsigned int loc = glGetUniformLocation(_program->getProgram(), "u_Model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));

        loc = glGetUniformLocation(_program->getProgram(), "u_View");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(_view));

        loc = glGetUniformLocation(_program->getProgram(), "u_Projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(_projection));

        // Do DrawCall
        glEnable(GL_DEPTH_TEST);
        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    

    glBindVertexArray(0);
}

void Lesson8::onExit()
{
    
}
}
}
