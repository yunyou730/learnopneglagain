#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene/BaseScene.h"
#include "Scene/Lesson1.h"
#include "Scene/Lesson2.h"
#include "Scene/Lesson3.h"
#include "Scene/Lesson4.h"
#include "Scene/Lesson5.h"
#include "Scene/Lesson6.h"
#include "Scene/Lesson7.h"

ayy::BaseScene* g_scene = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    if (g_scene != nullptr)
    {
		g_scene->setWindowSize(width, height);
    }
}

float CalculateDeltaTime()
{
    static float lastFrame = static_cast<float>(glfwGetTime());
    float currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return deltaTime;
}

int main(int argc, const char * argv[]) {
    printf("%d\n",2);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    

	int windowWidth = 800;
    int windowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //ayy::BaseScene* scene = new ayy::Lesson1();
    //ayy::BaseScene* scene = new ayy::lesson3::Lesson3();
    //ayy::BaseScene* scene = new ayy::l4::Lesson4();
    //ayy::BaseScene* scene = new ayy::l5::Lesson5();
    //ayy::BaseScene* scene = new ayy::l6::Lesson6();
    g_scene = new ayy::l7::Lesson7(windowWidth, windowHeight);
    g_scene->onEnter();
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        float deltaTime = CalculateDeltaTime();
        g_scene->onUpdate(deltaTime);
        g_scene->onRender();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    g_scene->onExit();
    delete g_scene;
    g_scene = nullptr;
    
    glfwTerminate();
    

    return 0;
}
