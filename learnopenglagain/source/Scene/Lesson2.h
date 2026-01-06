#pragma once
#include "BaseScene.h"
#include "../Common/ShaderProgram.h"

namespace ayy {
    class Lesson2 : public BaseScene
    {
    public:
        Lesson2();
        virtual ~Lesson2();
        
        virtual void onEnter() override;
        virtual void onUpdate(float deltaTime) override;
        virtual void onRender() override;
        virtual void onExit() override;
        
    private:
        float _vertices[24] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            1.0f, 0.0f, 0.0f,   // red
            
            0.5f, -0.5f, 0.0f,  // 右下角
            0.0f,  1.0f, 0.0f,  // green
            
            -0.5f, -0.5f, 0.0f, // 左下角
            0.0f, 0.0f, 1.0f,   // blue
            
            -0.5f, 0.5f, 0.0f,  // 左上角
            1.0f, 1.0f, 0.0f    // yellow
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
