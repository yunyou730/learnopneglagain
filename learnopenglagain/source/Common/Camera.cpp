#include "Camera.h"


namespace ayy
{

Camera::Camera()
{
	_viewMatrix = glm::mat4(1.0f);
	_projectionMatrix = glm::mat4(1.0f);
}

glm::mat4& Camera::getViewMatrix()
{
    return _viewMatrix;
}

glm::mat4& Camera::getProjectionMatrix()
{
    return _projectionMatrix;
}

void Camera::updateMatrix(float viewWidth, float viewHeight)
{
    _viewMatrix = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
    _projectionMatrix = glm::perspective(glm::radians(_fovY), viewWidth / viewHeight, _nearPlane, _farPlane);
}


void Camera::updateControl(GLFWwindow* window,float deltaTime)
{
    float moveOffset = _cameraMoveSpeed * deltaTime;
    float rotateOffset = _cameraRotateSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        _cameraPos += moveOffset * _cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        _cameraPos -= moveOffset * _cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        _cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * moveOffset;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        _cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * moveOffset;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        // 向左转
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, glm::radians(rotateOffset), _cameraUp);

        glm::vec4 front;
        front.x = _cameraFront.x;
        front.y = _cameraFront.y;
        front.z = _cameraFront.z;
        front.w = 0.0f;
        front = mat * front;
        _cameraFront = front;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        // 向右转
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, glm::radians(-rotateOffset), _cameraUp);

        glm::vec4 front;
        front.x = _cameraFront.x;
        front.y = _cameraFront.y;
        front.z = _cameraFront.z;
        front.w = 0.0f;
        front = mat * front;
        _cameraFront = front;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        glm::vec3 right = glm::normalize(glm::cross(_cameraFront, _cameraUp));

        // 仰头
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, glm::radians(rotateOffset), right);

        glm::vec4 front;
        front.x = _cameraFront.x;
        front.y = _cameraFront.y;
        front.z = _cameraFront.z;
        front.w = 0.0f;
        front = mat * front;
        _cameraFront = front;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        // 低头
        glm::vec3 right = glm::normalize(glm::cross(_cameraFront, _cameraUp));

        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, glm::radians(-rotateOffset), right);

        glm::vec4 front;
        front.x = _cameraFront.x;
        front.y = _cameraFront.y;
        front.z = _cameraFront.z;
        front.w = 0.0f;
        front = mat * front;
        _cameraFront = front;
    }
}

}