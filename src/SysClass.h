//System Class - Main Window Functions and loop
#pragma once
#define WIN32_LEAN_AND_MEAN

#include "glad\glad.h"
#include "glfw3.h"
#include "glm\glm.hpp"
#include <memory>
#include "RenderClass.h"
#include "TimerClass.h"
#include "InputClass.h"

class SysClass {
public:
    SysClass();
    SysClass(const SysClass&);
    ~SysClass();
    bool Init();

private:
    bool InitGlfwWindow();
    void Shutdown();
    bool InitClasses();
    void Loop();

    std::unique_ptr<RenderClass> c_Render;
    std::unique_ptr<TimerClass> c_Timer;
    std::unique_ptr<InputClass> c_Input;
    
    uint16_t m_MainWindowWidth = 800;
    uint16_t m_MainWindowHeight = 800;
    GLFWwindow* m_MainWindow = nullptr;
    int32_t m_FrameBufferHeight = 0;
    int32_t m_FrameBufferWidth = 0;
    GLuint m_RenderVAO = 0;

};