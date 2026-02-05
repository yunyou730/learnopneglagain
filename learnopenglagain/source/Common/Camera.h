#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace ayy
{
/*
    键盘 WASD, 控制摄像机前后左右移动
    键盘 上下左右，控制摄像机旋转
*/
class Camera
{
public:
    Camera();

    void updateMatrix(float viewWidth, float viewHeight);
    void updateControl(GLFWwindow* window,float deltaTime);

    glm::mat4& getViewMatrix();
    glm::mat4& getProjectionMatrix();

private:
	// View matrix parameters
    glm::vec3 _cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Projection matrix parameters
	float _fovY = 45.0f;            // in degrees
	float _nearPlane = 0.1f;
    float _farPlane = 100.0f;

    // Control parameters
    float _cameraMoveSpeed = 5.0f;
    float _cameraRotateSpeed = 60.0f;

    // cache matrix
    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
};
}
