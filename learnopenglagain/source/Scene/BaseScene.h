#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ayy
{
    class BaseScene
    {
    public:
        BaseScene(GLFWwindow* window,int width,int height)
            :_window(window)
            ,_windowWidth(width)
            ,_windowHeight(height)
        {
            
        }

        virtual ~BaseScene() {}
        
        virtual void onEnter() = 0;
        virtual void onUpdate(float deltaTime) = 0;
        virtual void onRender() = 0;
        virtual void onExit() = 0;

        void setWindowSize(int width, int height)
        {
            _windowWidth = width;
            _windowHeight = height;
        }
        
    protected:
        GLFWwindow* getWindow() const { return _window;}

    protected:
        int _windowWidth = 0;
		int _windowHeight = 0;
        GLFWwindow* _window = nullptr;
    };
}

