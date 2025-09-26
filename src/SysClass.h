//System Class - Main Window Functions and loop
#pragma once
#define WIN32_LEAN_AND_MEAN

#include "glad\glad.h"
#include "glfw3.h"
#include "glm\glm.hpp"

class SysClass {
public:
    SysClass();
    SysClass(const SysClass&);
    ~SysClass();
    bool Init();

private:
    bool InitGlfwWindow();
    void Shutdown();
    
    uint16_t m_MainWindowWidth = 1024;
    uint16_t m_MainWindowHeight = 1024;
    GLFWwindow* m_MainWindow = nullptr;
    int32_t m_FrameBufferHeight = 0;
    int32_t m_FrameBufferWidth = 0;
    GLuint m_RenderVAO = 0;

};