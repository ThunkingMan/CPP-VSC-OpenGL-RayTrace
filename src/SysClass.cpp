#include "SysClass.h"
#include <vector>

SysClass::SysClass() {}
SysClass::SysClass(const SysClass&) {}
SysClass::~SysClass() {}


bool SysClass::Init() {
    if (! glfwInit()) {
        std::printf("Error initilising GLFW.\n");
        return false;
    }
    if (InitGlfwWindow()) {
        std::printf("Error creating GLFW main window\n");
        return false;
    }
    if (! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {  //init GLAD
        std::printf("Error: Initilising GLAD.\n");
        Shutdown();
        return false;
    }
    //Classes
    
    // Game Loop
    
    Shutdown();
    return true;
}

bool SysClass::InitGlfwWindow() {
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

void SysClass::Shutdown() {
    if (m_MainWindow) glfwDestroyWindow(m_MainWindow);
    glfwTerminate();
}

