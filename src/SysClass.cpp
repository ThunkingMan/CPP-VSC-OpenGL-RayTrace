#include "SysClass.h"
#include <vector>

SysClass::SysClass() {}
SysClass::SysClass(const SysClass&) {}
SysClass::~SysClass() {}


bool Init() {
    return true;
}

bool SysClass::InitGlfw() {
    if (! glfwInit()) {
        std::printf("Error initilising GLFW.\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //core profile
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); //no tile bar or borders
    GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor(); //Get the primary monitor
    const GLFWvidmode* MonVidMode = glfwGetVideoMode(PrimaryMonitor); //get video mode of primary monitor
    uint16_t UpperLeftX = MonVidMode->width / 2 - m_MainWindowWidth / 2; //Calculate upper left to centre new window
    uint16_t UpperLeftY = MonVidMode->height / 2 - m_MainWindowHeight / 2;

    //Create main window
    m_MainWindow = glfwCreateWindow(m_MainWindowWidth, m_MainWindowHeight, "OpenGL Test", nullptr, nullptr);
    if (! m_MainWindow) {
        std::printf("Error: Creating main GLFW window.\n");
        glfwTerminate();
        return false;    
    }

    glfwSetWindowPos(m_MainWindow, UpperLeftX, UpperLeftY); //Centre the window
    glfwGetFramebufferSize(m_MainWindow, &m_FrameBufferWidth, &m_FrameBufferHeight); //Get frame buffer size
    glfwMakeContextCurrent(m_MainWindow); //Make the window's context current
    glfwSwapInterval(1); //Set Vsync
       
    return true;
}

void SysClass::CreateQuad() {
    struct VertexPosTex {
        glm::vec3 Pos;
        glm::vec2 Tex;
        VertexPosTex() {Pos=glm::vec3(0.0f, 0.0f, 0.0f); Tex = glm::vec2(0.0f, 0.0f);}
        VertexPosTex(glm::vec3 _Pos, glm::vec2 _Tex) {Pos = _Pos; Tex = _Tex;}
    };

    VertexPosTex Vertex[4] = {
        VertexPosTex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), //vert - top left
        VertexPosTex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)), //vert2 - bottom left
        VertexPosTex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)), //vert3 - Bottom right
        VertexPosTex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)) //vert4 - top right
    };

    

    
    

}

