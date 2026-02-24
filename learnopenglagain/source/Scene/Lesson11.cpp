#include "Lesson11.h"
#include <glad/glad.h>
#include "../Common/ShaderFileReader.h"
#include "../Common/Texture2D.h"
#include <GLFW/glfw3.h>

namespace ayy {
namespace l11 {

Lesson11::Lesson11(GLFWwindow* window,int width, int height)
	:BaseScene(window,width, height)
{
    _camera = new Camera();
}

Lesson11::~Lesson11()
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

    delete _diffuseTexture;
    _diffuseTexture = nullptr;

    delete _specularTexture;
    _specularTexture = nullptr;
}

void Lesson11::onEnter()
{
    glClearColor(0.1,0.1,0.1,1.0);
    initVertexData();
    initShader();
    initTexture();
}

void Lesson11::initVertexData()
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
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
            sizeof(VertexAttributePos),
            (void*)offsetof(VertexAttributePos, u));    // uv属性

        // 4. 开启 顶点属性
        glEnableVertexAttribArray(0);   // 开启 位置属性
		glEnableVertexAttribArray(1);   // 开启 法线属性
		glEnableVertexAttribArray(2);   // 开启 uv 属性
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

void Lesson11::initShader()
{
    std::string vertShaderCode = ShaderFileReader::readShaderCode("res/lesson11/lit_mat_with_tex.vert");
    std::string fragShaderCode = ShaderFileReader::readShaderCode("res/lesson11/lit_mat_with_tex.frag");
    _boxShader = new ShaderProgram(vertShaderCode, fragShaderCode);
    _boxShader->compileLink();

    vertShaderCode = ShaderFileReader::readShaderCode("res/common/light_vert.glsl");
    fragShaderCode = ShaderFileReader::readShaderCode("res/common/light_frag.glsl");
    _lightShader = new ShaderProgram(vertShaderCode, fragShaderCode);
    _lightShader->compileLink();
}

void Lesson11::initTexture()
{
    _diffuseTexture = new Texture2D();
    _diffuseTexture->load("res/lesson11/container2.png");

    _specularTexture = new Texture2D();
    _specularTexture->load("res/lesson11/container2_specular.png");
}

void Lesson11::onUpdate(float deltaTime)
{
    _camera->updateMatrix(_windowWidth, _windowHeight);
    _camera->updateControl(getWindow(), deltaTime);
}

void Lesson11::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    drawBox();
    drawLight();
}

void Lesson11::drawBox()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    glActiveTexture(GL_TEXTURE0);           // texture unit 0:diffuse texture
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getTextureHandle());

    glActiveTexture(GL_TEXTURE1);           // texture unit 1:specular texture
    glBindTexture(GL_TEXTURE_2D, _specularTexture->getTextureHandle());


    _boxShader->useProgram();
    _boxShader->setMat4("u_Model", model);
    _boxShader->setMat4("u_View", _camera->getViewMatrix());
    _boxShader->setMat4("u_Projection", _camera->getProjectionMatrix());
    
    _boxShader->setVec3("u_ViewPos",_camera->getPos());
    

    // @miao @todo
    _boxShader->setInt("u_Material.diffuse", 0);

    _boxShader->setVec3("u_Material.specular",0.5f,0.5f,0.5f);
    _boxShader->setFloat("u_Material.shininess",64.0f);
    
    // 光源颜色
    _lightColor.x = sin(glfwGetTime() * 2.0f);
    _lightColor.y = sin(glfwGetTime() * 0.7f);
    _lightColor.z = sin(glfwGetTime() * 1.3f);
    glm::vec3 diffuseColor = _lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
    
    _boxShader->setVec3("u_Light.ambient",ambientColor);
    _boxShader->setVec3("u_Light.diffuse",diffuseColor);
    _boxShader->setVec3("u_Light.specular",1.0f,1.0f,1.0f);
    _boxShader->setVec3("u_Light.position",_lightPos);
    
    glBindVertexArray(_boxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Lesson11::drawLight()
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

void Lesson11::onExit()
{
    
}
}
}
