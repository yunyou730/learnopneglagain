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
    
    glDeleteVertexArrays(1,&_VAO);
    glDeleteBuffers(1,&_VBO);

    delete _camera;
    _camera = nullptr;
}

void Lesson9::onEnter()
{
    glClearColor(0.5,0.8,0.2,1.0);
    initShader();
    initVertexData();
}

void Lesson9::initVertexData()
{
    // vertex data
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    // 1. bind VAO
    glBindVertexArray(_VAO);
    // 2. bind VBO, fill buffer data
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_boxVertices), _boxVertices, GL_STATIC_DRAW);

    // 4. Set Vertex attribute for binding VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(VertexAttributePos),
        (void*)offsetof(VertexAttributePos, x)); // 位置属性

    glEnableVertexAttribArray(0);   // 开启 位置属性
}

void Lesson9::initShader()
{
    std::string vertShaderCode = ShaderFileReader::readShaderCode("res/lesson9/color_object_vert.glsl");
    std::string fragShaderCode = ShaderFileReader::readShaderCode("res/lesson9/color_object_frag.glsl");
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
    //_program->useProgram();
    // @miao @todo

    glBindVertexArray(0);
}

void Lesson9::onExit()
{
    
}
}
}
