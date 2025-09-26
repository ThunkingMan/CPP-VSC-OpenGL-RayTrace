//Render Class
#pragma once
#include "glad\glad.h"
#include <string>

class RenderClass {
public:
    RenderClass();
    RenderClass(const RenderClass&);
    ~RenderClass();

    void Init();
    void Render();

private:
    void CreateDisplaySqr();
    std::string LoadFileToString(std::string FileName);
    bool CompileShaders(); 
        
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLuint m_ShaderProgram;

};