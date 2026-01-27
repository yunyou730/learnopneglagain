#include "Lesson4.h"
#include <glad/glad.h>
#include "../Common/ShaderFileReader.h"
#include "../Common/Texture2D.h"
#include <glm_0_9_8/glm.hpp>

namespace ayy {
namespace l4 {

Lesson4::Lesson4(int width, int height)
	:BaseScene(width, height)
{

}

Lesson4::~Lesson4()
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


void Lesson4::onEnter()
{
    initShader();
    initVertexData();
    initTexture();
}

void Lesson4::onUpdate(float deltaTime)
{
    
}

void Lesson4::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT);

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

void Lesson4::onExit()
{
    
}

void Lesson4::initVertexData()
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

void Lesson4::initShader()
{
    std::string vertShaderCode = ShaderFileReader::readShaderCode("res/lesson4/vert.glsl");
    std::string fragShaderCode = ShaderFileReader::readShaderCode("res/lesson4/frag.glsl");
    _program = new ShaderProgram(vertShaderCode,fragShaderCode);
    _program->compileLink();
}

void Lesson4::initTexture()
{
    _texture = new Texture2D();
    _texture->load("res/lesson4/container.jpg");

	_subTexture = new Texture2D();
    _subTexture->load("res/lesson4/awesomeface.png");

	glm::mat4 identity = glm::mat4(1.0f);
 //   glm::mat4 identity = glm::mat4();
}

}
}
