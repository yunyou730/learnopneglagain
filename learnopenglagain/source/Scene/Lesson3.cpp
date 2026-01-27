#include "Lesson3.h"
#include <glad/glad.h>
#include "../Common/ShaderFileReader.h"
#include "../Common/Texture2D.h"

namespace ayy {
namespace lesson3 {

Lesson3::Lesson3(int width, int height)
	:BaseScene(width, height)
{

}

Lesson3::~Lesson3()
{
    delete _program;
    _program = nullptr;
    
    glDeleteVertexArrays(1,&_VAO);
    glDeleteBuffers(1,&_VBO);
    glDeleteBuffers(1,&_EBO);
    
    delete _texture;
    _texture = nullptr;
}


void Lesson3::onEnter()
{
    initShader();
    initVertexData();
    initTexture();
}

void Lesson3::onUpdate(float deltaTime)
{
    
}

void Lesson3::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, _texture->getTextureHandle());
    _program->useProgram();
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Lesson3::onExit()
{
    
}

void Lesson3::initVertexData()
{
    // vertex data
    glGenVertexArrays(1,&_VAO);
    glGenBuffers(1,&_VBO);
    glGenBuffers(1,&_EBO);
    
    // 1. bind VAO
    glBindVertexArray(_VAO);
    // 2. bind VBO, fill buffer data
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(_vertices),_vertices,GL_STATIC_DRAW);
    
    // 3. bind EBO, fill buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(_indices),_indices,GL_STATIC_DRAW);
    
    // 4. Set Vertex attribute for binding VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(VertexAttribute),
                          (void*)offsetof(VertexAttribute,x)); // 位置属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(VertexAttribute),
                          (void*)offsetof(VertexAttribute,r));// 颜色属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          sizeof(VertexAttribute),
                          (void*)offsetof(VertexAttribute,u));// uv
    
    glEnableVertexAttribArray(0);   // 开启 位置属性
    glEnableVertexAttribArray(1);   // 开启 颜色属性
    glEnableVertexAttribArray(2);   // 开启 UV
}

void Lesson3::initShader()
{
    // shader
    std::string vertShaderCode = ShaderFileReader::readShaderCode("res/lesson3/vert.glsl");
    std::string fragShaderCode = ShaderFileReader::readShaderCode("res/lesson3/frag.glsl");
    _program = new ShaderProgram(vertShaderCode,fragShaderCode);
    _program->compileLink();
}

void Lesson3::initTexture()
{
    _texture = new Texture2D();
    _texture->load("res/lesson3/container.jpg");
    
}

}
}
