#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene/BaseScene.h"
#include "Scene/Lesson1.h"
#include "Scene/Lesson2.h"
#include "Scene/Lesson3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, const char * argv[]) {
    printf("%d\n",2);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
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
    ayy::BaseScene* scene = new ayy::lesson3::Lesson3();
    scene->onEnter();
    
    glClearColor(0.0,0.0,0.0,1.0);
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        scene->onUpdate(0.0f);
        scene->onRender();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    scene->onExit();
    delete scene;
    scene = nullptr;
    
    glfwTerminate();
    

    return 0;
}
