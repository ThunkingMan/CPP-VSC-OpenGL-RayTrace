#include "RenderClass.h"
#include "glm\glm.hpp"
#include <fstream>
#include <sstream>
#include "stb_image.h"


struct VertexPosTex {
    glm::vec3 Pos;
    glm::vec2 Tex;
    VertexPosTex() {Pos=glm::vec3(0.0f, 0.0f, 0.0f); Tex = glm::vec2(0.0f, 0.0f);}
    VertexPosTex(glm::vec3 _Pos, glm::vec2 _Tex) {Pos = _Pos; Tex = _Tex;}
};

void RenderClass::Render() {
    //Compute Shader
    glUseProgram(m_RayProgram);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_RayTexture);
    glDispatchCompute((GLuint)m_RayTextWidth , (GLuint)m_RayTextHeight, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS); // make sure writing to image has finished before read
    
    //Render
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_ShaderProgram);
    glBindVertexArray(m_VAO);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_RayTexture);
    //glBindTexture(GL_TEXTURE_2D, m_RayTexture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(m_MainWindow);
}

bool RenderClass::Init(GLFWwindow* MainWindow) {
    m_MainWindow = MainWindow;

    if(! CompileShaders()) {
        printf("Error compiling shaders.\n");
        return false;        
    }

    if (! CompileRayShader()) {
        printf("Error compiling compute shader.\n");
        return false;      
    }

    if (! LoadTestTexture()) {
         printf("Error loading shaders.\n");
         return false; 
    }
    
    
    LoadRaytexture();
    CreateDisplaySqr();
    return true;
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
    m_ShaderProgram = glCreateProgram();
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

bool RenderClass::LoadTestTexture() {
    std::string TextureFile = "assets\\wood_container.jpg";

    int TexWidth, TexHeight, TexChannels;
    unsigned char *TexData = nullptr;
    TexData = stbi_load(TextureFile.c_str(), &TexWidth, &TexHeight, &TexChannels, 0);
    if (! TexData) {
        printf("Error loading texture data from file.\n");
        return false;    
    }
    glGenTextures(1, &m_TestTexture); //Generate texture array - only one texture here
    glBindTexture(GL_TEXTURE_2D, m_TestTexture); //Bind the texture for modifications below
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TexWidth, TexHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, TexData); //Upload image data to bound texture
    glGenerateMipmap(GL_TEXTURE_2D); //generate mipmaps for bound texture
    
    stbi_image_free(TexData); //free the image data loaded from file
    
    return true;
}

bool RenderClass::LoadRaytexture() {
    glGenTextures(1, &m_RayTexture); //Create texture array (we create only one teture)
    //glActiveTexture(GL_TEXTURE0); //Select first  texture in array (we have only one texture in array)
    glBindTexture(GL_TEXTURE_2D, m_RayTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_RayTextWidth, m_RayTextHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindImageTexture(0, m_RayTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    return true;
}

void RenderClass::GetComputeWorkSize() {
    int WorkGrpCount[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &WorkGrpCount[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &WorkGrpCount[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &WorkGrpCount[2]);
    printf("max global (total) work group counts x:%i y:%i z:%i\n", WorkGrpCount[0], WorkGrpCount[1], WorkGrpCount[2]);
}

bool RenderClass::CompileRayShader() {
    std::string ComputeGLSLCode = LoadFileToString("shaders\\Compute.glsl");
    if (ComputeGLSLCode.empty()) {
        printf("Compute shader GLSL string is empty.\n");
        return false;
    }
    GLuint CompShaderObj = glCreateShader(GL_COMPUTE_SHADER);  //Cretae Shader Object
    if (CompShaderObj == 0) {
        printf("Error: Can not create compute shader object.\n");
        return false;
    }
    const char* ComputeShaderCode =  ComputeGLSLCode.c_str();
    glShaderSource(CompShaderObj, 1, &ComputeShaderCode, NULL);
    glCompileShader(CompShaderObj); //Compile shader code nad check success
    GLint IsSuccess;
    glGetShaderiv(CompShaderObj, GL_COMPILE_STATUS, &IsSuccess);
    if (!IsSuccess) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(CompShaderObj, 1024, NULL, InfoLog);
        printf("Error compiling compute shader '%s'\n", InfoLog);
        return false;
    }

    //Shader progrm
    m_RayProgram = glCreateProgram();
    glAttachShader(m_RayProgram, CompShaderObj); //Attach shader to program
    glLinkProgram(m_RayProgram);
    glGetProgramiv(m_RayProgram, GL_LINK_STATUS, &IsSuccess);
    if (!IsSuccess) {
        GLchar InfoLog[1024];
        printf("Error linking ray program: '%s'\n", InfoLog);
        return false;    
    }
    glDeleteShader(CompShaderObj);
    
    return true;
}


RenderClass::RenderClass() {}
RenderClass::RenderClass(const RenderClass&) {}
RenderClass::~RenderClass() {}
