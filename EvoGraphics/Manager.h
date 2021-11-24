#pragma once

#include "gl3w.h"
#include "glfw3.h"

#include <iostream>
#include <string.h>

#include "logger.h"

class GraphicsManager
{
public:
    static GraphicsManager* GetInstance();

	void init();
    void start();
    void render();
    void shutdown();

    void SetNewWindowValue(int w, int h);
    
private:
    // Only one instance
    GraphicsManager();
    ~GraphicsManager();
    static GraphicsManager* m_pCurrentInstance;

    static void WindowResizeCallBack(GLFWwindow* window, int w, int h);

private:
    bool m_bInit;
	uint32_t m_windowWidth;
	uint32_t m_windowHeight;
    uint32_t m_majorVersion;
    uint32_t m_minorVersion;
    //uint32_t samples;
    char m_windowTitle[128];
    GLFWwindow* m_mainWindow;

    bool m_bFlagsDebug;

    /*
    union
    {
        struct
        {
            unsigned int    fullscreen : 1;
            unsigned int    vsync : 1;
            unsigned int    cursor : 1;
            unsigned int    stereo : 1;
            unsigned int    debug : 1;
            unsigned int    robust : 1;
        };
        unsigned int        all;
    } flags;
    */

    GLuint program;     // temp
    GLuint vao;         // temp

    Logger* m_pLogger;
};