#include "RenderClass.h"
#include "glm\glm.hpp"
#include <fstream>
#include <sstream>


struct VertexPosTex {
    glm::vec3 Pos;
    glm::vec2 Tex;
    VertexPosTex() {Pos=glm::vec3(0.0f, 0.0f, 0.0f); Tex = glm::vec2(0.0f, 0.0f);}
    VertexPosTex(glm::vec3 _Pos, glm::vec2 _Tex) {Pos = _Pos; Tex = _Tex;}
};


RenderClass::RenderClass() {}
RenderClass::RenderClass(const RenderClass&) {}
RenderClass::~RenderClass() {}

void RenderClass::Init() {

}

void RenderClass::CreateDisplaySqr() {
    //Create square for display of raytrace texture
    
    VertexPosTex Vertex[4] = {
        VertexPosTex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), //vert - top left
        VertexPosTex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)), //vert2 - bottom left
        VertexPosTex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)), //vert3 - Bottom right
        VertexPosTex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)) //vert4 - top right
    };
    GLuint Index[] = {0, 1, 2, 2, 3, 0}; //Index data

    glGenVertexArrays(1, &m_VAO); //Create VAO
    glGenBuffers(1, &m_VBO); //Create VBO
    glGenBuffers(1, &m_EBO); //Cretae EBO
    glBindVertexArray(m_VAO); //Bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO); //BIND VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW); //Upload vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0); //Attribute 0 Vertex Position
    glEnableVertexAttribArray(0); //enable array atribute 0
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float))); //Attribute 1 texture position
    glEnableVertexAttribArray(1); //enable array atribute 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); //bind index buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index), Index, GL_STATIC_DRAW); //Upload index data
    glBindVertexArray(0); //Unbind VAO;
}

void RenderClass::Render() {

}

std::string RenderClass::LoadFileToString(std::string FileName) {
    std::ifstream InputFile(FileName, std::ios::in);
    if (! InputFile.is_open()) {
        std::printf("Error: Can not open file for conversion to string.\n");
        return "";       
    }
    std::stringstream StringStream;
    StringStream << InputFile.rdbuf();
    std::string ReturnString = StringStream.str();
    InputFile.close();
    return ReturnString;    
}

bool RenderClass::CompileShaders() {
    //Display vert shader
    std::string VertexGLSLCode = LoadFileToString("shaders\\Render.vert");
    if (VertexGLSLCode.empty()) {
        printf("Error: Vertex shader GLSL string is empty.\n");
        return false;
    }
    GLuint VertShaderObj = glCreateShader(GL_VERTEX_SHADER);  //Cretae Shader Object
    if (VertShaderObj == 0) {
        printf("Error: Can not create vertex shader object.\n");
        return false;
    }
    const char* VertexShaderCode =  VertexGLSLCode.c_str();
    glShaderSource(VertShaderObj, 1, &VertexShaderCode, NULL);
    glCompileShader(VertShaderObj); //Compile shader code nad check success
    GLint IsSuccess;
    glGetShaderiv(VertShaderObj, GL_COMPILE_STATUS, &IsSuccess);
    if (!IsSuccess) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(VertShaderObj, 1024, NULL, InfoLog);
        printf("Error compiling vertex shader type '%s'\n", InfoLog);
        return false;
    }
    
    //Display Frag shader
    std::string FragmentGLSLCode = LoadFileToString("shaders\\Render.frag");  //Load GLSL string from file
    if (FragmentGLSLCode.empty()) {
        printf("Error: Fragment shader GLSL string is empty.\n");
        return false;
    }
    GLuint FragShaderObj = glCreateShader(GL_FRAGMENT_SHADER);  //Cretae Shader Object
    if (FragShaderObj == 0) {
        printf("Error: Can not create fragment shader object.\n");
        return false;
    }
    const char* FragmentShaderCode =  FragmentGLSLCode.c_str();
    glShaderSource(FragShaderObj, 1, &FragmentShaderCode, NULL);
    glCompileShader(FragShaderObj); //Compile shader code nad check success
    IsSuccess;
    glGetShaderiv(FragShaderObj, GL_COMPILE_STATUS, &IsSuccess);
    if (!IsSuccess) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(VertShaderObj, 1024, NULL, InfoLog);
        printf("Error compiling fragment shader '%s'\n", InfoLog);
        return false;
    }

    //Shader progrm
    GLuint m_ShaderProgram = glCreateProgram();
    glAttachShader(m_ShaderProgram, VertShaderObj); //Attach shader to program
    glAttachShader(m_ShaderProgram, FragShaderObj);
    glLinkProgram(m_ShaderProgram);
    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &IsSuccess);
    if (!IsSuccess) {
        GLchar InfoLog[1024];
        printf("Error linking shader program: '%s'\n", InfoLog);
        return false;    
    }
    glDeleteShader(VertShaderObj);
    glDeleteShader(FragShaderObj);

    return true;
}






