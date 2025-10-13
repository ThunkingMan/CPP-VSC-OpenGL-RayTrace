//Movemnet Class
#pragma once

#define GLFW_INCLUDE_NONE //Do not load OpenGl gl.h with glfw3.h
#include "glfw3.h"
#include "glm\glm.hpp" // vec2, vec3, mat4, radians

class InputClass {
public:
    InputClass();
    InputClass(const InputClass&);
    ~InputClass();
    void Init(GLFWwindow* MainWindow, uint16_t m_mainWidowWidth, uint16_t m_MainWindowHeight);
    void ProcessInput(unsigned _int16 FrameDeltaMS);

    glm::vec3 m_Position;
    glm::vec3 m_Look; //Relative to origin, needs to translate by Position for camera look direction
    glm::vec3 m_Up; //Relative to origin, needs to translate by Position for camera look direction
    glm::vec3 m_Right; //Relative to origin, needs to translate by Position for camera look direction
    glm::mat4 m_CameraView;

private:
    GLFWwindow* m_MainWindow = nullptr;
    uint16_t m_mainWidowWidth = 0;
    uint16_t m_MainWindowHeight = 0;
        
    float m_MoveSpeed = 0.005f; //Move speed (meters per ms) - Human run speed approx 5m/s;
    float m_RotateSpeed;
    glm::mat4 m_IdentMatrix = glm::mat4(1.0f);

    float m_YawRads = 0; //Rotation around Y Axis 
};