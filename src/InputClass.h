//Input Class
#pragma once
#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "glm\glm.hpp"

class InputClass {
public:
    InputClass ();
    InputClass(const InputClass&);
    ~InputClass();

    void Init(GLFWwindow* MainWindow);
    void Process(unsigned short FrameDeltaMS);

private:
    GLFWwindow* m_MainWindow;

};