#pragma once

#include "glfw3.h"
//#include "gl3w.h"
#include <iostream>
#include <string.h>

class GraphicsManager
{
public:
	GraphicsManager() {};
	~GraphicsManager() {};

	void init();
private:
	uint32_t windowWidth;
	uint32_t windowHeight;
    uint32_t majorVersion;
    uint32_t minorVersion;
    uint32_t samples;
    char windowTitle[128];
    GLFWwindow* mainWindow;

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
};