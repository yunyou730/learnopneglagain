#pragma once
#include "BaseScene.h"
#include "../Common/ShaderProgram.h"

namespace ayy {
    class Lesson1 : public BaseScene
    {
    public:
        Lesson1();
        virtual ~Lesson1();
        
        virtual void onEnter() override;
        virtual void onUpdate(float deltaTime) override;
        virtual void onRender() override;
        virtual void onExit() override;
        
    private:
        float _vertices[9] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        
        unsigned int _VBO;
        unsigned int _VAO;
    
        ShaderProgram* _program = nullptr;
    };
}
