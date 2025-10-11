#include "SysClass.h"
#include <vector>
#include <memory>



void SysClass::Loop() {
    while (!glfwWindowShouldClose(m_MainWindow))
    {
        //c_Timer->GetDeltaTime(); //Get time since last frame
        //printf("%u\n", c_Timer->m_FrameDeltaMS);
        //c_Input->Process(c_Timer->m_FrameDeltaMS); //process input update view.
        c_Render->Render();
        glfwPollEvents(); //Poll for and process events
    }
}

bool SysClass::Init() {
    if (! glfwInit()) {
        std::printf("Error initilising GLFW.\n");
        return false;
    }
    if (! InitGlfwWindow()) {
        std::printf("Error creating GLFW main window\n");
        return false;
    }
    if (! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::printf("Error initilising GLAD.\n");
        Shutdown();
        return false;
    }
    
    //Classes
    if(! InitClasses()) {
        std::printf("Error initilising classes.\n");
        Shutdown();
        return false;        
    }
    
    Loop();
    Shutdown();
    return true;
}

bool SysClass::InitGlfwWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //core profile
   //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); //no tile bar or borders
    GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor(); //Get the primary monitor
    const GLFWvidmode* MonVidMode = glfwGetVideoMode(PrimaryMonitor); //get video mode of primary monitor
    uint16_t UpperLeftX = MonVidMode->width / 2 - m_MainWindowWidth / 2; //Calculate upper left to centre new window
    uint16_t UpperLeftY = MonVidMode->height / 2 - m_MainWindowHeight / 2;

    //Create main window
    m_MainWindow = glfwCreateWindow(m_MainWindowWidth, m_MainWindowHeight, "Ray Trace", nullptr, nullptr);
    if (! m_MainWindow) {
        std::printf("Error creating main GLFW window.\n");
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

bool SysClass::InitClasses() {
    c_Render = std::make_unique<RenderClass>();
 	if (! c_Render)
	{
		std::printf("Error creating Render Class.\n");
     	return false;
	}
    // std::unique_ptr<InputClass> c_Input = std::make_unique<InputClass>();
 	// if (! c_Input)
	// {
	// 	std::printf("Error creating Input Class.\n");
    //  	return false;
	// }
    std::unique_ptr<TimerClass> c_Timer = std::make_unique<TimerClass>();
 	if (! c_Timer)
	{
	    std::printf("Error creating Timer Class.\n");
        return false;
	}

    //Class Inits
    if(! c_Render->Init(m_MainWindow, m_MainWindowWidth, m_MainWindowHeight)) {
        std::printf("Error initialising Render Class.\n");
     	return false;    
    }
    //if (! c_Timer->Init()) {
    //    std::printf("Error initialising Timer Class.\n");
    // 	return false;    
    //}
       
    return true;   
}

SysClass::SysClass() {}
SysClass::SysClass(const SysClass&) {}
SysClass::~SysClass() {}

