//Render Class
#pragma once
#include "glad\glad.h"

class RenderClass {
public:
    RenderClass();
    RenderClass(const RenderClass&);
    ~RenderClass();

    void Init();
    void Render();

private:
     void CreateDisplaySqr();

    const char* VertShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTex;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos, 1.0);\n"
        "}\0";

    const char* FragShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D myTexture;\n"
        "void main()\n"
        "{\n"
        "FragColor = texture(myTexture, TexCoord);\n"
        "}\0";

    
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;

};