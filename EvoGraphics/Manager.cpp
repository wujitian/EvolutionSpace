#include "Manager.h"
#include "string"
#include "assert.h"

static void GlfwDebugCallBack(int error, const char* description)
{
    dprintf_d("[GLFW] GlfwDebugCallBack get in.");
    dprintf_e("[GLFW] Error: %s\n", description);
}

static void APIENTRY DebugCallStack(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
    dprintf_d("[GL_INFO] DebugCallStack get in.");
    dprintf_d("[GL_INFO] %s", message);
}

GraphicsManager::GraphicsManager()
{
    m_windowWidth = 800;
    m_windowHeight = 600;
    m_majorVersion = 4;
    m_minorVersion = 3;

    m_pLogger = new Logger();
    assert(m_pLogger);

    m_pLogger->init();

    dprintf_i("[GraphicsManager] Open ogl debug mode.");
    m_bFlagsDebug = true;

    m_pMeta = NULL;

    m_bInit = false;
}

GraphicsManager::~GraphicsManager()
{
    if (m_pLogger)
    {
        m_pLogger->deinit();
        delete m_pLogger;
    }
}

GraphicsManager* GraphicsManager::m_pCurrentInstance = NULL;
GraphicsManager* GraphicsManager::GetInstance()
{
    if (NULL == m_pCurrentInstance)
    {
        // lock
        m_pCurrentInstance = new GraphicsManager();
        if (!m_pCurrentInstance)
        {
            assert(0);      // error in allocation memory
            return NULL;
        }
        // unlock
    }

    return m_pCurrentInstance;
}

void GraphicsManager::SetMeta(Meta* pMeta)
{
    if (!pMeta)
    {
        dprintf_w("[GraphicsManager] GraphicsManager set invalid meta.");
    }

    if (m_pMeta)
    {
        dprintf_w("[GraphicsManager] GraphicsManager already have a meta.");
    }

    m_pMeta = pMeta;
}

void GraphicsManager::init()
{
    if (true == m_bInit)
    {
        dprintf_w("[GraphicsManager] GraphicsManager already inited.");
        return;
    }

    dprintf_i("[GraphicsManager] GraphicsManager init start.");

    strcpy_s(m_windowTitle, "GraphicsManager test");

    dprintf_i("[glfw] Set glfw error callback.");
    glfwSetErrorCallback(GlfwDebugCallBack);
    
    dprintf_i("[glfw] glfw init.");
    if (!glfwInit())
    {
        dprintf_e("Failed to initialize GLFW.");
        return;
    }

    dprintf_i("[glfw] set some glfw window information.");

    // set version information
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_minorVersion);

    // debug information
    if (m_bFlagsDebug)
    {
        // GLFW_OPENGL_DEBUG_CONTEXT specifies whether the context should be created in debug mode, 
        // which may provide additional error and diagnostic reporting functionality. Possible values are GLFW_TRUE and GLFW_FALSE.
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    // GLFW_CONTEXT_ROBUSTNESS specifies the robustness strategy to be used by the context. 
    // This can be one of GLFW_NO_RESET_NOTIFICATION or GLFW_LOSE_CONTEXT_ON_RESET, 
    // or GLFW_NO_ROBUSTNESS to not request a robustness strategy.
    glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);  

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality 
    // deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL version is 3.0 or above. 
    // If OpenGL ES is requested, this hint is ignored.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // GLFW_SAMPLES specifies the desired number of samples to use for multisampling. 
    // Zero disables multisampling. A value of GLFW_DONT_CARE means the application has no preference.
    glfwWindowHint(GLFW_SAMPLES, 0);    
    // GLFW_STEREO specifies whether to use OpenGL stereoscopic rendering. 
    // Possible values are GLFW_TRUE and GLFW_FALSE. This is a hard constraint.
    glfwWindowHint(GLFW_STEREO, GL_FALSE);  
                                            
    // full screen
    bool bFullScreen = false;
    if (bFullScreen) 
    {
        dprintf_i("[glfw] use full screen mode.");

        GLFWmonitor* pPrimaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* pMode = glfwGetVideoMode(pPrimaryMonitor);
        m_windowWidth = pMode->width;
        m_windowHeight = pMode->height;
        dprintf_i("[glfw] full screen size: width:%d, height:%d", m_windowWidth, m_windowHeight);
    }

    dprintf_i("[glfw] Create Window.");
    m_mainWindow = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowTitle, bFullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!m_mainWindow)
    {
        dprintf_e("[glfw] Failed to create window.");
        return;
    }

    //Before you can make OpenGL or OpenGL ES calls, you need to have a current context of the correct type. 
    //A context can only be current for a single thread at a time, and a thread can only have a single context current at a time.
    glfwMakeContextCurrent(m_mainWindow);

    //Set the number of screen updates to wait from the time glfwSwapBuffers was called before swapping the buffers and returning.
    //If the interval is zero, the swap will take place immediately when glfwSwapBuffers is called without waiting for a refresh.
    bool bVsync = false;
    if (bVsync == true)
    {
        int syncTime = 1;
        glfwSwapInterval(syncTime);  // not working : do not enable vSync?
    }

    glfwSetWindowSizeCallback(m_mainWindow, &GraphicsManager::WindowResizeCallBack);
    glfwSetKeyCallback(m_mainWindow, &GraphicsManager::WindowKeyCallback);
    glfwSetMouseButtonCallback(m_mainWindow, &GraphicsManager::MouseBottonCallback);
    glfwSetCursorPosCallback(m_mainWindow, &GraphicsManager::MouseMoveCallback);
    glfwSetScrollCallback(m_mainWindow, &GraphicsManager::MouseWheelCallback);
    //glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);  // whether to show cursor or not

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
    else
    {
        glDebugMessageCallbackARB((GLDEBUGPROC)DebugCallStack, this);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    }

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

    if (!m_pMeta)
    {
        dprintf_w("[GraphicsManager] need set meta first.");
        return;
    }

    m_pMeta->SetMetaTime((double)glfwGetTime());

    m_pMeta->start();
}

void GraphicsManager::render()
{
    if (false == m_bInit)
    {
        dprintf_w("[GraphicsManager] need init first.");
        return;
    }

    if (!m_pMeta)
    {
        dprintf_w("[GraphicsManager] need set meta first.");
        return;
    }

    bool renderRunning = true;

    while (renderRunning)
    {
        m_pMeta->SetMetaTime((double)glfwGetTime());

        m_pMeta->render();

        glfwSwapBuffers(m_mainWindow);
        glfwPollEvents();

        if (glfwWindowShouldClose(m_mainWindow))
        {
            renderRunning = false;
        }

        if (glfwGetKey(m_mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            renderRunning = false;
        }
    };
}

void GraphicsManager::shutdown()
{
    if (false == m_bInit)
    {
        dprintf_w("[GraphicsManager] need init first.");
        return;
    }

    m_pMeta->SetMetaTime((double)glfwGetTime());

    m_pMeta->shutdown();
}

// used for WindowResizeCallBack
void GraphicsManager::SetNewWindowValue(int w, int h)
{
    dprintf_i("[GraphicsManager] window set size: (%d, %d)", w, h);

    this->m_windowWidth = w;
    this->m_windowHeight = h;
}

// used for WindowKeyCallback
void GraphicsManager::SendWindowKeyMessage(int key, int scancode, int action, int mods)
{
    if (!m_pMeta)
    {
        dprintf_w("[GraphicsManager] need set meta first.");
        return;
    }

    m_pMeta->WindowKey(key, scancode, action, mods);
}

void GraphicsManager::WindowResizeCallBack(GLFWwindow* window, int w, int h)
{
    dprintf_i("[glfw] window resize: (%d, %d)", w, h);

    GraphicsManager* pCurrentInstance = GraphicsManager::GetInstance();
    pCurrentInstance->SetNewWindowValue(w, h);
}

void GraphicsManager::WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    dprintf_i("[glfw] key press : (%d, %d, %d, %d)", key, scancode, action, mods);

    GraphicsManager* pCurrentInstance = GraphicsManager::GetInstance();
    pCurrentInstance->SendWindowKeyMessage(key, scancode, action, mods);
}

void GraphicsManager::MouseBottonCallback(GLFWwindow* window, int button, int action, int mods)
{
    dprintf_i("[glfw] mouse botton press : (%d, %d, %d)", button, action, mods);
}

void GraphicsManager::MouseMoveCallback(GLFWwindow* window, double x, double y)
{
    //dprintf_i("[glfw] mouse move to: (%lf, %lf)", x, y);
}

void GraphicsManager::MouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    dprintf_i("[glfw] mouse wheel: (%lf, %lf)", xoffset, yoffset);
}