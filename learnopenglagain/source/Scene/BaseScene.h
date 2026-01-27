#pragma once

namespace ayy
{
    class BaseScene
    {
    public:
        BaseScene(int width,int height)
            :_windowWidth(width)
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
        int _windowWidth = 0;
		int _windowHeight = 0;
    };
}

