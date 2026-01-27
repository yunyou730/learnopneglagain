#include "Lesson1.h"
#include <glad/glad.h>

namespace ayy {

static const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

static const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
)";

Lesson1::Lesson1(int width,int height)
	:BaseScene(width, height)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    _program = new ShaderProgram(vertexShaderSource,fragmentShaderSource);
    _program->compileLink();
}

Lesson1::~Lesson1()
{
    delete _program;
    _program = nullptr;
    
    glDeleteVertexArrays(1,&_VAO);
    glDeleteBuffers(1,&_VBO);
    glDeleteBuffers(1,&_EBO);
}


void Lesson1::onEnter()
{
    
}

void Lesson1::onUpdate(float deltaTime)
{
    
}

void Lesson1::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
    _program->useProgram();
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Lesson1::onExit()
{
    
}

}
