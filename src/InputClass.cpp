#include "InputClass.h"
#include "glm\ext.hpp" // perspective, translate, rotate

InputClass::InputClass() {}
InputClass::InputClass(const InputClass&) {}
InputClass::~InputClass() {}

void InputClass::Init(GLFWwindow* MainWindow, uint16_t m_mainWidowWidth, uint16_t m_MainWindowHeight) {
    m_MainWindow = MainWindow; //Store main window pointer in class
    m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_Look = glm::vec3(0.0f, 0.0f, -1.0f);
    m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_Right = glm::cross(m_Look, m_Up);
    glfwSetCursorPos(m_MainWindow, 0, 0);
}

void InputClass::ProcessInput(unsigned _int16 FrameDeltaMS) {
    //Mouse movement.
    double MouseX, MouseY;
    glfwGetCursorPos(m_MainWindow, &MouseX, &MouseY); 
    //printf("Mouse: %f, %f\n", MouseX, MouseY);
    glfwSetCursorPos(m_MainWindow, 0, 0);
    
    //Yaw rotataion    
    float Yaw = 0 - MouseX / 10000; 
    glm::mat4 RotationMatrix = glm::rotate(m_IdentMatrix, Yaw, m_Up);
    glm::vec4 TmpVec4 = RotationMatrix * glm::vec4(m_Look, 1.0f);
    m_Look = glm::normalize(glm::vec3(TmpVec4)); //Rotate look vector
    m_Right = glm::cross(m_Look, m_Up); //Re-calc right vector

    //Pitch Rotation
    float Pitch = 0 - MouseY / 10000;
    RotationMatrix = glm::rotate(m_IdentMatrix, Pitch, m_Right);
    TmpVec4 = RotationMatrix * glm::vec4(m_Up, 1.0f);
    m_Up = glm::normalize(glm::vec3(TmpVec4)); //Rotate up vector
    m_Look = glm::cross(m_Up, m_Right); //Re-calc right vector

    //Roll
    float Roll = 0;
    if(glfwGetKey(m_MainWindow, GLFW_KEY_Q) == GLFW_PRESS) Roll += 0.1f;
    if(glfwGetKey(m_MainWindow, GLFW_KEY_E) == GLFW_PRESS) Roll -= 0.1f;
    RotationMatrix = glm::rotate(m_IdentMatrix, Roll, m_Look);
    TmpVec4 = RotationMatrix * glm::vec4(m_Up, 1.0f);
    m_Up = glm::normalize(glm::vec3(TmpVec4)); //Rotate up vector
    //m_Right = glm::cross();

    
    //Movement
    float FrameMoveDistance = m_MoveSpeed  * FrameDeltaMS; //Calculate possible distance moved in this frame
    if(glfwGetKey(m_MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(m_MainWindow, true);
    if(glfwGetKey(m_MainWindow, GLFW_KEY_W) == GLFW_PRESS) m_Position += m_Look * FrameMoveDistance;
    if(glfwGetKey(m_MainWindow, GLFW_KEY_S) == GLFW_PRESS) m_Position -= m_Look * FrameMoveDistance;
    if(glfwGetKey(m_MainWindow, GLFW_KEY_A) == GLFW_PRESS) m_Position -= m_Right * FrameMoveDistance;
    if(glfwGetKey(m_MainWindow, GLFW_KEY_D) == GLFW_PRESS) m_Position += m_Right * FrameMoveDistance;

    glm::vec3 CameraLook = m_Position + m_Look;
    glm::vec3 CameraUp = m_Position + m_Up;
    m_CameraView = glm::lookAt(m_Position, CameraLook, m_Up);
}