#include "Manager.h"
#include "string"
#include "assert.h"

void APIENTRY DebugCallStack(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
    dprintf_d("[GL_INFO] DebugCallStack get in.");
    dprintf_d("[GL_INFO] %s", message);
}

GraphicsManager::GraphicsManager()
{
    windowWidth = 800;
    windowHeight = 600;
    majorVersion = 4;
    minorVersion = 3;

    // [todo] need check, if have two GraphicsManager, then do not need two logger class...
    pLogger = new Logger();
    assert(pLogger);

    pLogger->init();

    dprintf_i("[GraphicsManager] Open ogl debug mode.");
    bFlagsDebug = true;

    m_bInit = false;
}

GraphicsManager::~GraphicsManager()
{
    if (pLogger)
    {
        pLogger->deinit();
        delete pLogger;
    }
}

GraphicsManager* GraphicsManager::pCurrentInstance = NULL;
GraphicsManager* GraphicsManager::GetInstance()
{
    if (NULL == pCurrentInstance)
    {
        // lock
        pCurrentInstance = new GraphicsManager();
        if (!pCurrentInstance)
        {
            assert(0);      // error in allocation memory
            return NULL;
        }
        // unlock
    }

    return pCurrentInstance;
}

void GraphicsManager::init()
{
    if (true == m_bInit)
    {
        dprintf_w("[GraphicsManager] GraphicsManager already inited.");
        return;
    }

    dprintf_i("[GraphicsManager] GraphicsManager init start.");

    strcpy_s(windowTitle, "GraphicsManager test");
    
    dprintf_i("[glfw] glfw init.");
    if (!glfwInit())
    {
        dprintf_e("Failed to initialize GLFW.");
        return;
    }

    dprintf_i("[glfw] set some glfw window information.");

    // set version information
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

    // debug information
    if (bFlagsDebug)
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
        dprintf_i("[glfw] use full screen.");

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
        dprintf_i("[glfw] do not use full screen.");

        mainWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, bFullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
        if (!mainWindow)
        {
            dprintf_e("[glfw] Failed to open window.");
            return;
        }
    }

    glfwMakeContextCurrent(mainWindow);

    glfwSetWindowSizeCallback(mainWindow, &GraphicsManager::WindowResizeCallBack);
    //glfwSetKeyCallback(mainWindow, glfw_onKey);
    //glfwSetMouseButtonCallback(mainWindow, glfw_onMouseButton);
    //glfwSetCursorPosCallback(mainWindow, glfw_onMouseMove);
    //glfwSetScrollCallback(mainWindow, glfw_onMouseWheel);
    //glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);  // whether to show cursor or not

    gl3wInit();
    dprintf_i("[glfw] gl3w init.");

    // print debug version information
    dprintf_d("[GL_INFO] VENDOR: %s", (char*)glGetString(GL_VENDOR));
    dprintf_d("[GL_INFO] VERSION: %s", (char*)glGetString(GL_VERSION));
    dprintf_d("[GL_INFO] RENDERER: %s", (char*)glGetString(GL_RENDERER));

    if (gl3wIsSupported(4, 3))
    {
        dprintf_i("[glfw] gl3w supported version (4, 3).");
        glDebugMessageCallback((GLDEBUGPROC)DebugCallStack, nullptr);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    }
    /*
    else if (sb6IsExtensionSupported("GL_ARB_debug_output"))
    {
        glDebugMessageCallbackARB((GLDEBUGPROC)debug_callback, this);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    }
    */

    dprintf_i("[GraphicsManager] GraphicsManager init end.");
    m_bInit = true;
}

void GraphicsManager::start()
{
    if (false == m_bInit)
    {
        dprintf_w("[GraphicsManager] need init first.");
        return;
    }

    static const char* vs_source[] =
    {
        "#version 420 core                                                 \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
        "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
        "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
        "                                                                  \n"
        "    gl_Position = vertices[gl_VertexID];                          \n"
        "}                                                                 \n"
    };

    static const char* fs_source[] =
    {
        "#version 420 core                                                 \n"
        "                                                                  \n"
        "out vec4 color;                                                   \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
        "}                                                                 \n"
    };

    program = glCreateProgram();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, fs_source, NULL);
    glCompileShader(fs);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, vs_source, NULL);
    glCompileShader(vs);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void GraphicsManager::render()
{
    if (false == m_bInit)
    {
        dprintf_w("[GraphicsManager] need init first.");
        return;
    }

    bool renderRunning = true;

    while (renderRunning)
    {
        //render(glfwGetTime());

        // temp code
        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // temp code end

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();

        if (glfwWindowShouldClose(mainWindow))
        {
            renderRunning = false;
        }

        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            renderRunning = false;
        }
    };

    OutputDebugStringA("My output string.");
}

void GraphicsManager::shutdown()
{
    if (false == m_bInit)
    {
        dprintf_w("[GraphicsManager] need init first.");
        return;
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
}

// used for WindowResizeCallBack
void GraphicsManager::SetNewWindowValue(int w, int h)
{
    dprintf_i("[GraphicsManager] window set size: (%d, %d)", w, h);

    this->windowWidth = w;
    this->windowHeight = h;
}

void GraphicsManager::WindowResizeCallBack(GLFWwindow* window, int w, int h)
{
    dprintf_i("[glfw] window resize: (%d, %d)", w, h);

    GraphicsManager* pCurrentInstance = GraphicsManager::GetInstance();
    pCurrentInstance->SetNewWindowValue(w, h);
}