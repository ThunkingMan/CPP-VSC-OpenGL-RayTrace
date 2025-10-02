//Render Class
#pragma once
#include "glad\glad.h"
#include "glfw3.h"
#include <string>

class RenderClass {
public:
    RenderClass();
    RenderClass(const RenderClass&);
    ~RenderClass();

    bool Init(GLFWwindow* mMainWindow);
    void Render();

    

private:
    void CreateDisplaySqr();
    std::string LoadFileToString(std::string FileName);
    bool CompileShaders();
    bool LoadTestTexture();
    bool LoadRaytexture();
    void GetComputeWorkSize();
    bool CompileRayShader();
    void GetWorkGroupSize();

    
    GLFWwindow* m_MainWindow = nullptr;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLuint m_ShaderProgram;
    GLuint m_TestTexture;

    uint16_t m_RayTextWidth = 512;
    uint16_t m_RayTextHeight = 512;
    GLuint m_RayTexture;
    GLuint m_RayProgram;
    

};