#include "Lesson5.h"
#include <glad/glad.h>
#include "../Common/ShaderFileReader.h"
#include "../Common/Texture2D.h"
//#include "glm"

namespace ayy {
namespace l5 {

Lesson5::Lesson5()
{

}

Lesson5::~Lesson5()
{
    delete _program;
    _program = nullptr;
    
    glDeleteVertexArrays(1,&_VAO);
    glDeleteBuffers(1,&_VBO);
    glDeleteBuffers(1,&_EBO);
    
    delete _texture;
    _texture = nullptr;

    delete _subTexture;
	_subTexture = nullptr;
}


void Lesson5::onEnter()
{
    glClearColor(0.5,0.8,0.2,1.0);
    initShader();
    initVertexData();
    initTexture();
}

void Lesson5::onUpdate(float deltaTime)
{
//    float _rotAngle = 0.0f;
//    glm::mat4 trans;
    
}

void Lesson5::onRender()
{
    glActiveTexture(GL_TEXTURE0);   // texture unit 0
    glBindTexture(GL_TEXTURE_2D, _texture->getTextureHandle());     // bind texture unit 0 with texture handle

	glActiveTexture(GL_TEXTURE1);   // texture unit 1
    glBindTexture(GL_TEXTURE_2D, _subTexture->getTextureHandle());  // bind texture unit 1 with texture handle

    _program->useProgram();
	_program->setInt("u_MainTex", 0);   // bind texture unit 0 to shader uniform
    _program->setInt("u_SecondTex", 1); // bind texture unit 1 to shader uniform

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Lesson5::onExit()
{
    
}

void Lesson5::initVertexData()
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

void Lesson5::initShader()
{
    std::string vertShaderCode = ShaderFileReader::readShaderCode("res/lesson4/vert.glsl");
    std::string fragShaderCode = ShaderFileReader::readShaderCode("res/lesson4/frag.glsl");
    _program = new ShaderProgram(vertShaderCode,fragShaderCode);
    _program->compileLink();
}

void Lesson5::initTexture()
{
    _texture = new Texture2D();
    _texture->load("res/lesson4/container.jpg");

	_subTexture = new Texture2D();
    _subTexture->load("res/lesson4/awesomeface.png");
}

}
}
