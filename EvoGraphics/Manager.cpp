#include "Manager.h"

void GraphicsManager::init()
{
    strcpy_s(windowTitle, "GraphicsManager test");

    if (!glfwInit())
    {
        //fprintf(stderr, "Failed to initialize GLFW\n");
        std::cout << "[Error] Failed to initialize GLFW" << std::endl;
        return;
    }

    // set version information
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

    // debug information
    if (0)
    {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    if (0)  // robust
    {
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 0);        // info.samples
    glfwWindowHint(GLFW_STEREO, GL_FALSE);    // info.flags.stereo ? GL_TRUE : GL_FALSE

    // full screen
    bool bFullScreen = false;
    if (bFullScreen)       // info.flags.fullscreen
    {
        /*
        if (info.windowWidth == 0 || info.windowHeight == 0)
        {
            GLFWvidmode mode;
            glfwGetDesktopMode(&mode);
            info.windowWidth = mode.Width;
            info.windowHeight = mode.Height;
        }

        glfwOpenWindow(info.windowWidth, info.windowHeight, 8, 8, 8, 0, 32, 0, GLFW_FULLSCREEN);
        glfwSwapInterval((int)info.flags.vsync);
        */
    }
    else
    {
        mainWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, bFullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
        if (!mainWindow)
        {
            fprintf(stderr, "Failed to open window\n");
            return;
        }
    }

    glfwMakeContextCurrent(mainWindow);

    //glfwSetWindowSizeCallback(mainWindow, glfw_onResize);
    //glfwSetKeyCallback(mainWindow, glfw_onKey);
    //glfwSetMouseButtonCallback(mainWindow, glfw_onMouseButton);
    //glfwSetCursorPosCallback(mainWindow, glfw_onMouseMove);
    //glfwSetScrollCallback(mainWindow, glfw_onMouseWheel);
    //glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);  // whether to show cursor or not

    //gl3wInit();
}