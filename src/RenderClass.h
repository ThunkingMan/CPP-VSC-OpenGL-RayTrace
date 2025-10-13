//Render Class
#pragma once
#include "glad\glad.h"
#include "glfw3.h"
#include "glm\glm.hpp"
#include <string>

class RenderClass {
public:
    RenderClass();
    RenderClass(const RenderClass&);
    ~RenderClass();

    bool Init(GLFWwindow* MainWindow, uint16_t MainWindowWidth, uint16_t MainWindowHeight);
    void Render(glm::vec3 Look);

private:
    void CreateDisplaySqr();
    std::string LoadFileToString(std::string FileName);
    bool CompileShaders();
    bool LoadTestTexture();
    bool LoadRaytexture();
    bool CompileRayShader();
    void GetWorkGroupSize();
    bool CreateSSBO();

    
    GLFWwindow* m_MainWindow = nullptr;
    uint16_t m_MainWindowWidth = 0;
    uint16_t m_MainWindowHeight = 0;
    uint16_t m_MainWindowXCnt = 0;
    uint16_t m_MainWindowYCnt = 0;
    
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLuint m_ShaderProgram;
    GLuint m_TestTexture;
    GLuint m_SSBO;
    
    GLuint m_RayTexture;
    GLuint m_RayProgram;
    

};