#include "Lesson2.h"
#include <glad/glad.h>
#include "../Common/ShaderFileReader.h"

namespace ayy {
namespace lesson2 {

Lesson2::Lesson2(GLFWwindow* window,int width, int height)
    :BaseScene(window,width,height)
{
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
    glEnableVertexAttribArray(0);   // 开启 位置属性
    glEnableVertexAttribArray(1);   // 开启 颜色属性
    
    std::string vertShaderCode = ShaderFileReader::readShaderCode("res/lesson2/test_vert.glsl");
    std::string fragShaderCode = ShaderFileReader::readShaderCode("res/lesson2/test_frag.glsl");
    _program = new ShaderProgram(vertShaderCode,fragShaderCode);
    _program->compileLink();
}

Lesson2::~Lesson2()
{
    delete _program;
    _program = nullptr;
    
    glDeleteVertexArrays(1,&_VAO);
    glDeleteBuffers(1,&_VBO);
    glDeleteBuffers(1,&_EBO);
}


void Lesson2::onEnter()
{
    
}

void Lesson2::onUpdate(float deltaTime)
{
    
}

void Lesson2::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
    _program->useProgram();
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Lesson2::onExit()
{
    
}

}
}
