#pragma once

#include "gl3w.h"
#include "glfw3.h"

#include <iostream>
#include <string.h>

#include "logger.h"
#include "Meta.h"

class GraphicsManager
{
public:
    static GraphicsManager* GetInstance();

	void init();
    void start();
    void render();
    void shutdown();

    void SetMeta(Meta* pMeta);
    void SetNewWindowValue(int w, int h);
    
private:
    // Only one instance
    GraphicsManager();
    ~GraphicsManager();
    static GraphicsManager* m_pCurrentInstance;

    static void WindowResizeCallBack(GLFWwindow* window, int w, int h);
    static void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseBottonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseMoveCallback(GLFWwindow* window, double x, double y);
    static void MouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    bool m_bInit;
	uint32_t m_windowWidth;
	uint32_t m_windowHeight;
    uint32_t m_majorVersion;
    uint32_t m_minorVersion;
    char m_windowTitle[128];
    GLFWwindow* m_mainWindow;

    Meta* m_pMeta;
    double m_passedTime;

    bool m_bFlagsDebug;

    GLuint program;     // temp
    GLuint vao;         // temp

    Logger* m_pLogger;
};