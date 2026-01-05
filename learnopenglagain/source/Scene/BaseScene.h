#pragma once

namespace ayy
{
    class BaseScene
    {
    public:
        BaseScene() {}
        virtual ~BaseScene() {}
        
        virtual void onEnter() = 0;
        virtual void onUpdate(float deltaTime) = 0;
        virtual void onRender() = 0;
        virtual void onExit() = 0;
    };
}

