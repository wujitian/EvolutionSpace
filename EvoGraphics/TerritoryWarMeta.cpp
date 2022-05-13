#include "TerritoryWarMeta.h"

TerritoryWarMeta::TerritoryWarMeta()
{
	dprintf_i("[TerritoryWarMeta] TerritoryWarMeta create.");

	program = 0;
	vao = 0;
}

TerritoryWarMeta::~TerritoryWarMeta()
{
	dprintf_i("[TerritoryWarMeta] TerritoryWarMeta destroy.");
}

void TerritoryWarMeta::start(void)
{
    dprintf_i("[TerritoryWarMeta] TerritoryWarMeta start() get in. <time=%lf>", m_metaPassedTime);

    static const char* vs_source[] =
    {
        "#version 420 core                                                 \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    const vec4 vertices[] = vec4[](vec4(-0.25,  0.25, 0.5, 1.0),  \n"
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
        "    color = vec4(1.0, 0.2, 0.2, 1.0);                             \n"
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

static void RenderPrint(double passedTime)
{
    static double timeThreshold = 0.0f;

    if (passedTime > timeThreshold)
    {
        dprintf_i("[TerritoryWarMeta] TerritoryWarMeta render() get in. <time=%lf>", passedTime);

        timeThreshold += 1.0f;
    }
}

void TerritoryWarMeta::render(void)
{
    RenderPrint(m_metaPassedTime);

    // temp code
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, green);

    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // temp code end
}

void TerritoryWarMeta::shutdown(void)
{
    dprintf_i("[TerritoryWarMeta] TerritoryWarMeta shutdown() get in.  <time=%lf>", m_metaPassedTime);

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
}