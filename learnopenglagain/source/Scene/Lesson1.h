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
        float _vertices[12] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
        };
        
        unsigned int _indices[6] = {
            0,1,3,  // 第一个三角形
            1,2,3   // 第二个三角形
        };
        
        unsigned int _VBO;
        unsigned int _VAO;
        unsigned int _EBO;
    
        ShaderProgram* _program = nullptr;
    };
}
