// Input Class - Keyboard and Mouse
#include "InputClass.h"

InputClass::InputClass () {}
InputClass::InputClass(const InputClass&) {}
InputClass::~InputClass() {}

void InputClass::Init(GLFWwindow* MainWindow) {
    m_MainWindow = MainWindow;   
}

void InputClass::Process(unsigned short FrameDeltaMS) {
    if(glfwGetKey(m_MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(m_MainWindow, true);
}   
