#include "Manager.h"
#include "string"

GraphicsManager::GraphicsManager()
{
    windowWidth = 800;
    windowHeight = 600;
    majorVersion = 4;
    minorVersion = 3;
}

GraphicsManager::~GraphicsManager()
{
}

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

    gl3wInit();

    // print version
    //fprintf(stderr, "VENDOR: %s\n", (char*)glGetString(GL_VENDOR));
    //fprintf(stderr, "VERSION: %s\n", (char*)glGetString(GL_VERSION));
    //fprintf(stderr, "RENDERER: %s\n", (char*)glGetString(GL_RENDERER));

    /*
    if (gl3wIsSupported(4, 3))
    {
        glDebugMessageCallback((GLDEBUGPROC)debug_callback, this);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    }
    else if (sb6IsExtensionSupported("GL_ARB_debug_output"))
    {
        glDebugMessageCallbackARB((GLDEBUGPROC)debug_callback, this);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    }
    */
}

void GraphicsManager::start()
{
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

    /*
    AllocConsole();
    FILE* pOut;
    freopen_s(&pOut, "conin$", "w", stdin);
    freopen_s(&pOut, "conout$", "w", stdout);
    freopen_s(&pOut, "conout$", "w", stderr);

    std::cout << "Rendering finished." << std::endl;
    printf("Test cout.\n");

    fclose(pOut);
    FreeConsole();
    */
}

void GraphicsManager::shutdown()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
}