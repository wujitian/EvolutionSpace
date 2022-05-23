#include "MagicCubeMeta.h"
#include <random>

/// <summary>
/// CubeBasic class
/// </summary>

CubeBasic::CubeBasic(float x, float y, float z, vec3 color_front, vec3 color_back,
    vec3 color_top, vec3 color_bottom, vec3 color_left, vec3 color_right)
    : x_(x), y_(y), z_(z),
    color_front_(color_front), color_back_(color_back),
    color_top_(color_top), color_bottom_(color_bottom),
    color_left_(color_left), color_right_(color_right)
{
    dprintf_i("[CubeBasic] CubeBasic create.");
}

CubeBasic::~CubeBasic()
{
    dprintf_i("[CubeBasic] CubeBasic destroy.");

    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void CubeBasic::SetCenterCoords(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

void CubeBasic::SetColors(vec3 color_front, vec3 color_back, vec3 color_top, vec3 color_bottom,
    vec3 color_left, vec3 color_right)
{
    color_front_ = color_front;
    color_back_ = color_back;
    color_top_ = color_top;
    color_bottom_ = color_bottom;
    color_left_ = color_left;
    color_right_ = color_right;
}

void CubeBasic::Init(GLuint program)
{
    program_ = program;

    glUseProgram(program_);
    
    model_matrix_ = glGetUniformLocation(program_, "model_matrix");
    projection_matrix_ = glGetUniformLocation(program_, "projection_matrix");

    GLfloat cube_vertices[] =
    {
        x_ - 1.0f, y_ - 1.0f, z_ - 1.0f, 1.0f, x_ + 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f, x_ + 1.0f, y_ - 1.0f, z_ - 1.0f, 1.0f,  // back  
        x_ + 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f, x_ - 1.0f, y_ - 1.0f, z_ - 1.0f, 1.0f, x_ - 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f,
        x_ - 1.0f, y_ - 1.0f, z_ - 1.0f, 1.0f, x_ + 1.0f, y_ - 1.0f, z_ - 1.0f, 1.0f, x_ - 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f,  // bottom  
        x_ + 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f, x_ - 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f, x_ + 1.0f, y_ - 1.0f, z_ - 1.0f, 1.0f,
        x_ - 1.0f, y_ - 1.0f, z_ - 1.0f, 1.0f, x_ - 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f, x_ - 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f,  // left 
        x_ - 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f, x_ - 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f, x_ - 1.0f, y_ + 1.0f, z_ + 1.0f, 1.0f,
        x_ + 1.0f, y_ - 1.0f, z_ - 1.0f, 1.0f, x_ + 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f, x_ + 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f,  // right 
        x_ + 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f, x_ + 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f, x_ + 1.0f, y_ + 1.0f, z_ + 1.0f, 1.0f,
        x_ + 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f, x_ - 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f, x_ - 1.0f, y_ + 1.0f, z_ + 1.0f, 1.0f,  // top 
        x_ + 1.0f, y_ + 1.0f, z_ - 1.0f, 1.0f, x_ - 1.0f, y_ + 1.0f, z_ + 1.0f, 1.0f, x_ + 1.0f, y_ + 1.0f, z_ + 1.0f, 1.0f,
        x_ - 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f, x_ + 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f, x_ + 1.0f, y_ + 1.0f, z_ + 1.0f, 1.0f,  // front  
        x_ + 1.0f, y_ + 1.0f, z_ + 1.0f, 1.0f, x_ - 1.0f, y_ + 1.0f, z_ + 1.0f, 1.0f, x_ - 1.0f, y_ - 1.0f, z_ + 1.0f, 1.0f,
    };

    GLfloat cube_colors[12 * 12];
    int base = 0;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i * 4 + 0] = color_back_[0];
        cube_colors[base + i * 4 + 1] = color_back_[1];
        cube_colors[base + i * 4 + 2] = color_back_[2];
        cube_colors[base + i * 4 + 3] = 1.0;
    }
    base = 24;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i * 4 + 0] = color_bottom_[0];
        cube_colors[base + i * 4 + 1] = color_bottom_[1];
        cube_colors[base + i * 4 + 2] = color_bottom_[2];
        cube_colors[base + i * 4 + 3] = 1.0;
    }
    base = 48;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i * 4 + 0] = color_left_[0];
        cube_colors[base + i * 4 + 1] = color_left_[1];
        cube_colors[base + i * 4 + 2] = color_left_[2];
        cube_colors[base + i * 4 + 3] = 1.0;
    }
    base = 72;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i * 4 + 0] = color_right_[0];
        cube_colors[base + i * 4 + 1] = color_right_[1];
        cube_colors[base + i * 4 + 2] = color_right_[2];
        cube_colors[base + i * 4 + 3] = 1.0;
    }
    base = 96;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i * 4 + 0] = color_top_[0];
        cube_colors[base + i * 4 + 1] = color_top_[1];
        cube_colors[base + i * 4 + 2] = color_top_[2];
        cube_colors[base + i * 4 + 3] = 1.0;
    }
    base = 120;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i * 4 + 0] = color_front_[0];
        cube_colors[base + i * 4 + 1] = color_front_[1];
        cube_colors[base + i * 4 + 2] = color_front_[2];
        cube_colors[base + i * 4 + 3] = 1.0;
    }
   
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices) + sizeof(cube_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_vertices), cube_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_vertices), sizeof(cube_colors), cube_colors);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_vertices));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void CubeBasic::Draw(mat4 projection_matrix, mat4 model_matrix)
{
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glUniformMatrix4fv(projection_matrix_, 1, GL_FALSE, projection_matrix);
    glUniformMatrix4fv(model_matrix_, 1, GL_FALSE, model_matrix);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/// <summary>
/// CubeUnit class
/// </summary>

CubeUnit::CubeUnit()
{
    dprintf_i("[CubeUnit] CubeUnit create.");
}

CubeUnit::~CubeUnit()
{
    dprintf_i("[CubeUnit] CubeUnit destroy.");
}

void CubeUnit::SetCenterCoords(float x, float y, float z)
{
    m_position = vmath::vec3(x, y, z);
    m_cube.SetCenterCoords(x, y, z);
}

void CubeUnit::SetColors(vmath::vec3 front, vmath::vec3 back, vmath::vec3 top, vmath::vec3 bottom,
    vmath::vec3 left, vmath::vec3 right)
{
    m_colorFront = front;
    m_colorBack = back;
    m_colorTop = top;
    m_colorBottom = bottom;
    m_colorLeft = left;
    m_colorRight = right;
    m_cube.SetColors(front, back, top, bottom, left, right);
}

void CubeUnit::Init(GLuint program)
{
    m_program = program;
    m_cube.Init(m_program);
}

void CubeUnit::MatrixInit(void)
{
    // Set up the model and projection matrix
    //vmath::mat4 view_projection_matrix = vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 500.0f);
    vmath::mat4 view_projection_matrix = vmath::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -30.0f, 30.0f);
    vmath::mat4 eye_matrix = vmath::lookat(vec3(8.0f, 8.0f, 0.0f), vec3(0.0f, 0.0f, -10.0f), vec3(0.0, 1.0, 0.0));
    m_projection_matrix = view_projection_matrix * eye_matrix;
    m_base_model_matrix = vmath::translate(0.0f, 0.0f, -10.0f);
    m_angle_model_matrix = vmath::rotate(0.0f, vec3(0.0f, 0.0f, 1.0f));
}

void CubeUnit::SetMove(float angle_x, float angle_y, float angle_z)
{
    if (true == m_bRunning)
    {
        dprintf_w("[CubeUnit] Please wait action finish!");
        return;
    }

    m_var_angle_x = angle_x;
    m_var_angle_y = angle_y;
    m_var_angle_z = angle_z;

    m_bRunning = true;
}

bool CubeUnit::IsRunning(void)
{
    return m_bRunning;
}

void CubeUnit::Draw(void)
{
    bool bIn = false;
    if (m_var_angle_x > THRESHOLD)
    {
        m_angle_model_matrix = vmath::rotate(STRIDE, vec3(1.0f, 0.0f, 0.0f)) * m_angle_model_matrix;
        m_var_angle_x -= STRIDE;
        bIn = true;
    }
    else if (m_var_angle_x < -THRESHOLD)
    {
        m_angle_model_matrix = vmath::rotate(-STRIDE, vec3(1.0f, 0.0f, 0.0f)) * m_angle_model_matrix;
        m_var_angle_x += STRIDE;
        bIn = true;
    }

    if (m_var_angle_y > THRESHOLD)
    {
        m_angle_model_matrix = vmath::rotate(STRIDE, vec3(0.0f, 1.0f, 0.0f)) * m_angle_model_matrix;
        m_var_angle_y -= STRIDE;
        bIn = true;
    }
    else if (m_var_angle_y < -THRESHOLD)
    {
        m_angle_model_matrix = vmath::rotate(-STRIDE, vec3(0.0f, 1.0f, 0.0f)) * m_angle_model_matrix;
        m_var_angle_y += STRIDE;
        bIn = true;
    }

    if (m_var_angle_z > THRESHOLD)
    {
        m_angle_model_matrix = vmath::rotate(STRIDE, vec3(0.0f, 0.0f, 1.0f)) * m_angle_model_matrix;
        m_var_angle_z -= STRIDE;
        bIn = true;
    }
    else if (m_var_angle_z < -THRESHOLD)
    {
        m_angle_model_matrix = vmath::rotate(-STRIDE, vec3(0.0f, 0.0f, 1.0f)) * m_angle_model_matrix;
        m_var_angle_z += STRIDE;
        bIn = true;
    }

    if (false == bIn)
    {
        m_bRunning = false;
    }

    m_cube.Draw(m_projection_matrix, m_base_model_matrix * m_angle_model_matrix);
}

/// <summary>
/// MagicCube class
/// </summary>

bool MagicCube::s_bProgramInited = false;
GLuint MagicCube::s_magicCubeProgram = 0;

MagicCube::MagicCube()
{
    dprintf_i("[MagicCube] MagicCube create.");
}

MagicCube::~MagicCube()
{
    dprintf_i("[MagicCube] MagicCube destroy.");

    if (pCubes_)
    {
        delete []pCubes_;
        pCubes_ = nullptr;
    }
}

bool MagicCube::InitProgram()
{
    if (s_bProgramInited)
    {
        return true;
    }

    dprintf_i("[MagicCube] InitProgram start.");

    static const char* vs_source[] =
    {
        "#version 330                                                      \n"
        "                                                                  \n"
        "uniform mat4 model_matrix;                                        \n"
        "uniform mat4 projection_matrix;                                   \n"
        "                                                                  \n"
        "layout (location = 0) in vec4 position;                           \n"
        "layout (location = 1) in vec4 color;                              \n"
        "                                                                  \n"
        "out vec4 vs_fs_color;                                             \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    vs_fs_color = color;                                          \n"
        "                                                                  \n"
        "    gl_Position = projection_matrix * (model_matrix * position);  \n"
        "}                                                                 \n"
    };

    static const char* fs_source[] =
    {
        "#version 330                                                      \n"
        "                                                                  \n"
        "in vec4 vs_fs_color;                                              \n"
        "layout (location = 0) out vec4 color;                             \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    color = vs_fs_color;                                          \n"
        "}                                                                 \n"
    };

    s_magicCubeProgram = glCreateProgram();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, fs_source, NULL);
    glCompileShader(fs);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, vs_source, NULL);
    glCompileShader(vs);

    glAttachShader(s_magicCubeProgram, vs);
    glAttachShader(s_magicCubeProgram, fs);

    glLinkProgram(s_magicCubeProgram);

    s_bProgramInited = true;

    return true;
}

bool MagicCube::DestoryProgram()
{
    if (!s_bProgramInited)
    {
        return true;
    }

    dprintf_i("[MagicCube] DestoryProgram.");

    glUseProgram(0);
    glDeleteProgram(s_magicCubeProgram);

    s_bProgramInited = false;

    return true;
}

bool MagicCube::Init()
{
    dprintf_i("[MagicCube] Init MagicCube.");

    if (!s_bProgramInited)
    {
        InitProgram();
    }

    // new magic cube and init
    pCubes_ = new CubeUnit[27];
    
    pCubes_[0].SetCenterCoords(-LEN, LEN, LEN);
    pCubes_[0].SetColors(RED, BLACK, YELLOW, BLACK, BLUE, BLACK);
    pCubes_[0].Init(s_magicCubeProgram);
    pCubes_[1].SetCenterCoords(0.0f, LEN, LEN);
    pCubes_[1].SetColors(RED, BLACK, YELLOW, BLACK, BLACK, BLACK);
    pCubes_[1].Init(s_magicCubeProgram);
    pCubes_[2].SetCenterCoords(LEN, LEN, LEN);
    pCubes_[2].SetColors(RED, BLACK, YELLOW, BLACK, BLACK, GREEN);
    pCubes_[2].Init(s_magicCubeProgram);
    pCubes_[3].SetCenterCoords(-LEN, 0.0f, LEN);
    pCubes_[3].SetColors(RED, BLACK, BLACK, BLACK, BLUE, BLACK);
    pCubes_[3].Init(s_magicCubeProgram);
    pCubes_[4].SetCenterCoords(0.0f, 0.0f, LEN);
    pCubes_[4].SetColors(RED, BLACK, BLACK, BLACK, BLACK, BLACK);
    pCubes_[4].Init(s_magicCubeProgram);
    pCubes_[5].SetCenterCoords(LEN, 0.0f, LEN);
    pCubes_[5].SetColors(RED, BLACK, BLACK, BLACK, BLACK, GREEN);
    pCubes_[5].Init(s_magicCubeProgram);
    pCubes_[6].SetCenterCoords(-LEN, -LEN, LEN);
    pCubes_[6].SetColors(RED, BLACK, BLACK, WHITE, BLUE, BLACK);
    pCubes_[6].Init(s_magicCubeProgram);
    pCubes_[7].SetCenterCoords(0.0f, -LEN, LEN);
    pCubes_[7].SetColors(RED, BLACK, BLACK, WHITE, BLACK, BLACK);
    pCubes_[7].Init(s_magicCubeProgram);
    pCubes_[8].SetCenterCoords(LEN, -LEN, LEN);
    pCubes_[8].SetColors(RED, BLACK, BLACK, WHITE, BLACK, GREEN);
    pCubes_[8].Init(s_magicCubeProgram);
    pCubes_[9].SetCenterCoords(-LEN, LEN, 0.0f);
    pCubes_[9].SetColors(BLACK, BLACK, YELLOW, BLACK, BLUE, BLACK);
    pCubes_[9].Init(s_magicCubeProgram);
    pCubes_[10].SetCenterCoords(0.0f, LEN, 0.0f);
    pCubes_[10].SetColors(BLACK, BLACK, YELLOW, BLACK, BLACK, BLACK);
    pCubes_[10].Init(s_magicCubeProgram);
    pCubes_[11].SetCenterCoords(LEN, LEN, 0.0f);
    pCubes_[11].SetColors(BLACK, BLACK, YELLOW, BLACK, BLACK, GREEN);
    pCubes_[11].Init(s_magicCubeProgram);
    pCubes_[12].SetCenterCoords(-LEN, 0.0f, 0.0f);
    pCubes_[12].SetColors(BLACK, BLACK, BLACK, BLACK, BLUE, BLACK);
    pCubes_[12].Init(s_magicCubeProgram);
    pCubes_[13].SetCenterCoords(0.0f, 0.0f, 0.0f);
    pCubes_[13].SetColors(BLACK, BLACK, BLACK, BLACK, BLACK, BLACK);
    pCubes_[13].Init(s_magicCubeProgram);
    pCubes_[14].SetCenterCoords(LEN, 0.0f, 0.0f);
    pCubes_[14].SetColors(BLACK, BLACK, BLACK, BLACK, BLACK, GREEN);
    pCubes_[14].Init(s_magicCubeProgram);
    pCubes_[15].SetCenterCoords(-LEN, -LEN, 0.0f);
    pCubes_[15].SetColors(BLACK, BLACK, BLACK, WHITE, BLUE, BLACK);
    pCubes_[15].Init(s_magicCubeProgram);
    pCubes_[16].SetCenterCoords(0.0f, -LEN, 0.0f);
    pCubes_[16].SetColors(BLACK, BLACK, BLACK, WHITE, BLACK, BLACK);
    pCubes_[16].Init(s_magicCubeProgram);
    pCubes_[17].SetCenterCoords(LEN, -LEN, 0.0f);
    pCubes_[17].SetColors(BLACK, BLACK, BLACK, WHITE, BLACK, GREEN);
    pCubes_[17].Init(s_magicCubeProgram);
    pCubes_[18].SetCenterCoords(-LEN, LEN, -LEN);
    pCubes_[18].SetColors(BLACK, ORANGE, YELLOW, BLACK, BLUE, BLACK);
    pCubes_[18].Init(s_magicCubeProgram);
    pCubes_[19].SetCenterCoords(0.0f, LEN, -LEN);
    pCubes_[19].SetColors(BLACK, ORANGE, YELLOW, BLACK, BLACK, BLACK);
    pCubes_[19].Init(s_magicCubeProgram);
    pCubes_[20].SetCenterCoords(LEN, LEN, -LEN);
    pCubes_[20].SetColors(BLACK, ORANGE, YELLOW, BLACK, BLACK, GREEN);
    pCubes_[20].Init(s_magicCubeProgram);
    pCubes_[21].SetCenterCoords(-LEN, 0.0f, -LEN);
    pCubes_[21].SetColors(BLACK, ORANGE, BLACK, BLACK, BLUE, BLACK);
    pCubes_[21].Init(s_magicCubeProgram);
    pCubes_[22].SetCenterCoords(0.0f, 0.0f, -LEN);
    pCubes_[22].SetColors(BLACK, ORANGE, BLACK, BLACK, BLACK, BLACK);
    pCubes_[22].Init(s_magicCubeProgram);
    pCubes_[23].SetCenterCoords(LEN, 0.0f, -LEN);
    pCubes_[23].SetColors(BLACK, ORANGE, BLACK, BLACK, BLACK, GREEN);
    pCubes_[23].Init(s_magicCubeProgram);
    pCubes_[24].SetCenterCoords(-LEN, -LEN, -LEN);
    pCubes_[24].SetColors(BLACK, ORANGE, BLACK, WHITE, BLUE, BLACK);
    pCubes_[24].Init(s_magicCubeProgram);
    pCubes_[25].SetCenterCoords(0.0f, -LEN, -LEN);
    pCubes_[25].SetColors(BLACK, ORANGE, BLACK, WHITE, BLACK, BLACK);
    pCubes_[25].Init(s_magicCubeProgram);
    pCubes_[26].SetCenterCoords(LEN, -LEN, -LEN);
    pCubes_[26].SetColors(BLACK, ORANGE, BLACK, WHITE, BLACK, GREEN);
    pCubes_[26].Init(s_magicCubeProgram);

    for (int i = 0; i < 27; ++i)
    {
        cubeIds_[i] = i;
        pCubes_[i].MatrixInit();
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // set background color

    return true;
}

bool MagicCube::Draw()
{
    // dprintf_i("[MagicCube] Draw start.");

    // todo:: check init

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup
    glEnable(GL_CULL_FACE);
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT, GL_FILL);  // need check

    glUseProgram(s_magicCubeProgram);

    for (int i = 0; i < 27; ++i)
    {
        pCubes_[i].Draw();
    }

    //cout << "[0] ==> " << cubeIds_[0] << "," << cubeIds_[1] << "," << cubeIds_[2] << endl;
    //cout << "[1] ==> " << cubeIds_[3] << "," << cubeIds_[4] << "," << cubeIds_[5] << endl;
    //cout << "[2] ==> " << cubeIds_[6] << "," << cubeIds_[7] << "," << cubeIds_[8] << endl;
    //cout << "[3] ==> " << cubeIds_[9] << "," << cubeIds_[10] << "," << cubeIds_[11] << endl;
    //cout << "[4] ==> " << cubeIds_[12] << "," << cubeIds_[13] << "," << cubeIds_[14] << endl;
    //cout << "[5] ==> " << cubeIds_[15] << "," << cubeIds_[16] << "," << cubeIds_[17] << endl;
    //cout << "[6] ==> " << cubeIds_[18] << "," << cubeIds_[19] << "," << cubeIds_[20] << endl;
    //cout << "[7] ==> " << cubeIds_[21] << "," << cubeIds_[22] << "," << cubeIds_[23] << endl;
    //cout << "[8] ==> " << cubeIds_[24] << "," << cubeIds_[25] << "," << cubeIds_[26] << endl;

    return true;
}

bool MagicCube::CanMove(void)
{
    for (int i = 0; i < 27; ++i)
        if (true == pCubes_[i].IsRunning())
            return false;
    return true;
}

void MagicCube::SwithID_ClockWise(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2)
{
    int temp = cubeIds_[x0];
    cubeIds_[x0] = cubeIds_[z0];
    cubeIds_[z0] = cubeIds_[z2];
    cubeIds_[z2] = cubeIds_[x2];
    cubeIds_[x2] = temp;
    temp = cubeIds_[x1];
    cubeIds_[x1] = cubeIds_[y0];
    cubeIds_[y0] = cubeIds_[z1];
    cubeIds_[z1] = cubeIds_[y2];
    cubeIds_[y2] = temp;
}

void MagicCube::SwithID_Reverse(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2)
{
    int temp = cubeIds_[x0];
    cubeIds_[x0] = cubeIds_[z2];
    cubeIds_[z2] = temp;
    temp = cubeIds_[x1];
    cubeIds_[x1] = cubeIds_[z1];
    cubeIds_[z1] = temp;
    temp = cubeIds_[x2];
    cubeIds_[x2] = cubeIds_[z0];
    cubeIds_[z0] = temp;
    temp = cubeIds_[y0];
    cubeIds_[y0] = cubeIds_[y2];
    cubeIds_[y2] = temp;
}

void MagicCube::SwithID_AntiClockWise(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2)
{
    int temp = cubeIds_[x0];
    cubeIds_[x0] = cubeIds_[x2];
    cubeIds_[x2] = cubeIds_[z2];
    cubeIds_[z2] = cubeIds_[z0];
    cubeIds_[z0] = temp;
    temp = cubeIds_[x1];
    cubeIds_[x1] = cubeIds_[y2];
    cubeIds_[y2] = cubeIds_[z1];
    cubeIds_[z1] = cubeIds_[y0];
    cubeIds_[y0] = temp;
}

// Move Functions
void MagicCube::Move_F1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(0, 1, 2, 3, 4, 5, 6, 7, 8);
    for (int i = 0; i < 9; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -90.0f);
}

void MagicCube::Move_F2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(0, 1, 2, 3, 4, 5, 6, 7, 8);
    for (int i = 0; i < 9; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -180.0f);
}

void MagicCube::Move_F3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(0, 1, 2, 3, 4, 5, 6, 7, 8);
    for (int i = 0; i < 9; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, 90.0f);
}

void MagicCube::Move_U1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(18, 19, 20, 9, 10, 11, 0, 1, 2);
    for (int i = 0; i < 27; i = i + 9)
    {
        pCubes_[cubeIds_[i + 0]].SetMove(0.0f, -90.0f, 0.0f);
        pCubes_[cubeIds_[i + 1]].SetMove(0.0f, -90.0f, 0.0f);
        pCubes_[cubeIds_[i + 2]].SetMove(0.0f, -90.0f, 0.0f);
    }
}

void MagicCube::Move_U2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(18, 19, 20, 9, 10, 11, 0, 1, 2);
    for (int i = 0; i < 27; i = i + 9)
    {
        pCubes_[cubeIds_[i + 0]].SetMove(0.0f, -180.0f, 0.0f);
        pCubes_[cubeIds_[i + 1]].SetMove(0.0f, -180.0f, 0.0f);
        pCubes_[cubeIds_[i + 2]].SetMove(0.0f, -180.0f, 0.0f);
    }
}

void MagicCube::Move_U3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(18, 19, 20, 9, 10, 11, 0, 1, 2);
    for (int i = 0; i < 27; i = i + 9)
    {
        pCubes_[cubeIds_[i + 0]].SetMove(0.0f, 90.0f, 0.0f);
        pCubes_[cubeIds_[i + 1]].SetMove(0.0f, 90.0f, 0.0f);
        pCubes_[cubeIds_[i + 2]].SetMove(0.0f, 90.0f, 0.0f);
    }
}

void MagicCube::Move_R1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 2; i < 27; i = i + 3)
        pCubes_[cubeIds_[i]].SetMove(-90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_R2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 2; i < 27; i = i + 3)
        pCubes_[cubeIds_[i]].SetMove(-180.0f, 0.0f, 0.0f);
}

void MagicCube::Move_R3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 2; i < 27; i = i + 3)
        pCubes_[cubeIds_[i]].SetMove(90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_B1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(20, 19, 18, 23, 22, 21, 26, 25, 24);
    for (int i = 18; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, 90.0f);
}

void MagicCube::Move_B2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(20, 19, 18, 23, 22, 21, 26, 25, 24);
    for (int i = 18; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, 180.0f);
}

void MagicCube::Move_B3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(20, 19, 18, 23, 22, 21, 26, 25, 24);
    for (int i = 18; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -90.0f);
}

void MagicCube::Move_D1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(6, 7, 8, 15, 16, 17, 24, 25, 26);
    for (int i = 0; i < 27; i = i + 9)
    {
        pCubes_[cubeIds_[i + 6]].SetMove(0.0f, 90.0f, 0.0f);
        pCubes_[cubeIds_[i + 7]].SetMove(0.0f, 90.0f, 0.0f);
        pCubes_[cubeIds_[i + 8]].SetMove(0.0f, 90.0f, 0.0f);
    }
}

void MagicCube::Move_D2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(6, 7, 8, 15, 16, 17, 24, 25, 26);
    for (int i = 0; i < 27; i = i + 9)
    {
        pCubes_[cubeIds_[i + 6]].SetMove(0.0f, 180.0f, 0.0f);
        pCubes_[cubeIds_[i + 7]].SetMove(0.0f, 180.0f, 0.0f);
        pCubes_[cubeIds_[i + 8]].SetMove(0.0f, 180.0f, 0.0f);
    }
}

void MagicCube::Move_D3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(6, 7, 8, 15, 16, 17, 24, 25, 26);
    for (int i = 0; i < 27; i = i + 9)
    {
        pCubes_[cubeIds_[i + 6]].SetMove(0.0f, -90.0f, 0.0f);
        pCubes_[cubeIds_[i + 7]].SetMove(0.0f, -90.0f, 0.0f);
        pCubes_[cubeIds_[i + 8]].SetMove(0.0f, -90.0f, 0.0f);
    }
}

void MagicCube::Move_L1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(18, 9, 0, 21, 12, 3, 24, 15, 6);
    for (int i = 0; i < 27; i = i + 3)
        pCubes_[cubeIds_[i]].SetMove(90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_L2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(18, 9, 0, 21, 12, 3, 24, 15, 6);
    for (int i = 0; i < 27; i = i + 3)
        pCubes_[cubeIds_[i]].SetMove(180.0f, 0.0f, 0.0f);
}

void MagicCube::Move_L3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(18, 9, 0, 21, 12, 3, 24, 15, 6);
    for (int i = 0; i < 27; i = i + 3)
        pCubes_[cubeIds_[i]].SetMove(-90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_X1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(0, 9, 18, 3, 12, 21, 6, 15, 24);
    SwithID_ClockWise(1, 10, 19, 4, 13, 22, 7, 16, 25);
    SwithID_ClockWise(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 0; i < 27; i++)
        pCubes_[cubeIds_[i]].SetMove(-90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_X2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(0, 9, 18, 3, 12, 21, 6, 15, 24);
    SwithID_Reverse(1, 10, 19, 4, 13, 22, 7, 16, 25);
    SwithID_Reverse(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 0; i < 27; i++)
        pCubes_[cubeIds_[i]].SetMove(-180.0f, 0.0f, 0.0f);
}

void MagicCube::Move_X3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(0, 9, 18, 3, 12, 21, 6, 15, 24);
    SwithID_AntiClockWise(1, 10, 19, 4, 13, 22, 7, 16, 25);
    SwithID_AntiClockWise(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 0; i < 27; i++)
        pCubes_[cubeIds_[i]].SetMove(90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_Y1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(18, 19, 20, 9, 10, 11, 0, 1, 2);
    SwithID_ClockWise(21, 22, 23, 12, 13, 14, 3, 4, 5);
    SwithID_ClockWise(24, 25, 26, 15, 16, 17, 6, 7, 8);
    for (int i = 0; i < 27; i++)
    {
        pCubes_[cubeIds_[i]].SetMove(0.0f, -90.0f, 0.0f);
    }
}

void MagicCube::Move_Y2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(18, 19, 20, 9, 10, 11, 0, 1, 2);
    SwithID_Reverse(21, 22, 23, 12, 13, 14, 3, 4, 5);
    SwithID_Reverse(24, 25, 26, 15, 16, 17, 6, 7, 8);
    for (int i = 0; i < 27; i++)
    {
        pCubes_[cubeIds_[i]].SetMove(0.0f, -180.0f, 0.0f);
    }
}

void MagicCube::Move_Y3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(18, 19, 20, 9, 10, 11, 0, 1, 2);
    SwithID_AntiClockWise(21, 22, 23, 12, 13, 14, 3, 4, 5);
    SwithID_AntiClockWise(24, 25, 26, 15, 16, 17, 6, 7, 8);
    for (int i = 0; i < 27; i++)
    {
        pCubes_[cubeIds_[i]].SetMove(0.0f, 90.0f, 0.0f);
    }
}

void MagicCube::Move_Z1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(0, 1, 2, 3, 4, 5, 6, 7, 8);
    SwithID_ClockWise(9, 10, 11, 12, 13, 14, 15, 16, 17);
    SwithID_ClockWise(18, 19, 20, 21, 22, 23, 24, 25, 26);
    for (int i = 0; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -90.0f);
}

void MagicCube::Move_Z2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(0, 1, 2, 3, 4, 5, 6, 7, 8);
    SwithID_Reverse(9, 10, 11, 12, 13, 14, 15, 16, 17);
    SwithID_Reverse(18, 19, 20, 21, 22, 23, 24, 25, 26);
    for (int i = 0; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -180.0f);
}

void MagicCube::Move_Z3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(0, 1, 2, 3, 4, 5, 6, 7, 8);
    SwithID_AntiClockWise(9, 10, 11, 12, 13, 14, 15, 16, 17);
    SwithID_AntiClockWise(18, 19, 20, 21, 22, 23, 24, 25, 26);
    for (int i = 0; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, 90.0f);
}

void MagicCube::RandomShuffle(void)
{
    std::default_random_engine e0, e1;
    e0.seed(10);
    e1.seed(10);
    std::uniform_int_distribution<unsigned> u0(0, 8);
    std::uniform_int_distribution<unsigned> u1(0, 2);

    for (int i = 0; i < 20; ++i)
    {
        int t0 = u0(e0);
        int t1 = u1(e1);

        dprintf_i("[MagicCube] step %d: [%d, %d]", i, t0, t1);

        switch (t0)
        {
        case 0:
            if (t1 == 0)
                Move_F1();
            else if (t1 == 1)
                Move_F2();
            else if (t1 == 2)
                Move_F3();
            break;
        case 1:
            if (t1 == 0)
                Move_U1();
            else if (t1 == 1)
                Move_U2();
            else if (t1 == 2)
                Move_U3();
            break;
        case 2:
            if (t1 == 0)
                Move_R1();
            else if (t1 == 1)
                Move_R2();
            else if (t1 == 2)
                Move_R3();
            break;
        case 3:
            if (t1 == 0)
                Move_B1();
            else if (t1 == 1)
                Move_B2();
            else if (t1 == 2)
                Move_B3();
            break;
        case 4:
            if (t1 == 0)
                Move_D1();
            else if (t1 == 1)
                Move_D2();
            else if (t1 == 2)
                Move_D3();
            break;
        case 5:
            if (t1 == 0)
                Move_L1();
            else if (t1 == 1)
                Move_L2();
            else if (t1 == 2)
                Move_L3();
            break;
        case 6:
            if (t1 == 0)
                Move_X1();
            else if (t1 == 1)
                Move_X2();
            else if (t1 == 2)
                Move_X3();
            break;
        case 7:
            if (t1 == 0)
                Move_Y1();
            else if (t1 == 1)
                Move_Y2();
            else if (t1 == 2)
                Move_Y3();
            break;
        case 8:
            if (t1 == 0)
                Move_Z1();
            else if (t1 == 1)
                Move_Z2();
            else if (t1 == 2)
                Move_Z3();
            break;
        default:
            break;
        }

        while (!CanMove())
        {
            Draw();
        }
    }
}

/// <summary>
/// MagicCubeMeta class
/// </summary>

MagicCubeMeta::MagicCubeMeta()
{
    dprintf_i("[MagicCubeMeta] MagicCubeMeta create.");

    m_pMagicCube = nullptr;

    m_bKeyOn = false;
    m_preKey = GLFW_KEY_UNKNOWN;
}

MagicCubeMeta::~MagicCubeMeta()
{
    dprintf_i("[MagicCubeMeta] MagicCubeMeta destroy.");

    if (m_pMagicCube)
    {
        delete m_pMagicCube;
    }

    if (MagicCube::DestoryProgram())
    {
        dprintf_w("[MagicCubeMeta] Destroy MagicCube program failed.");
    }
}

void MagicCubeMeta::start(void)
{
    dprintf_i("[MagicCubeMeta] MagicCubeMeta start() get in. <time=%lf>", m_metaPassedTime);

    if (m_pMagicCube)
    {
        dprintf_w("[MagicCubeMeta] MagicCube object already exists!");

        delete m_pMagicCube;
        m_pMagicCube = nullptr;
    }

    m_pMagicCube = new MagicCube();
    if (!m_pMagicCube)
    {
        dprintf_e("[MagicCubeMeta] New MagicCube object failed!");
        return;
    }

    if (!m_pMagicCube->Init())
    {
        dprintf_e("[MagicCubeMeta] Init MagicCube object failed!");
        return;
    }
}

static void RenderPrint(double passedTime)
{
    static double timeThreshold = 0.0f;

    if (passedTime > timeThreshold)
    {
        dprintf_i("[MagicCubeMeta] MagicCubeMeta render() get in. <time=%lf>", passedTime);

        timeThreshold += 1.0f;
    }
}

void MagicCubeMeta::render(void)
{
    RenderPrint(m_metaPassedTime);

    if (!m_pMagicCube->Draw())
    {
        dprintf_e("[MagicCubeMeta] Call MagicCube::Draw failed!");
        return;
    }
}

void MagicCubeMeta::shutdown(void)
{
    dprintf_i("[MagicCubeMeta] MagicCubeMeta shutdown() get in.  <time=%lf>", m_metaPassedTime);

    delete m_pMagicCube;
    m_pMagicCube = nullptr;
}

void MagicCubeMeta::WindowKey(int key, int scancode, int action, int mods)
{
    dprintf_i("[MagicCubeMeta] key press : (%d, %d, %d, %d)", key, scancode, action, mods);

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_F:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_F;
            return;
        case GLFW_KEY_U:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_U;
            return;
        case GLFW_KEY_R:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_R;
            return;
        case GLFW_KEY_B:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_B;
            return;
        case GLFW_KEY_D:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_D;
            return;
        case GLFW_KEY_L:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_L;
            return;
        case GLFW_KEY_X:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_X;
            return;
        case GLFW_KEY_Y:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_Y;
            return;
        case GLFW_KEY_Z:
            m_bKeyOn = true;
            m_preKey = GLFW_KEY_Z;
            return;
        case GLFW_KEY_1:
            if (true == m_bKeyOn)
            {
                if (m_preKey == GLFW_KEY_F)
                    m_pMagicCube->Move_F1();
                else if (m_preKey == GLFW_KEY_U)
                    m_pMagicCube->Move_U1();
                else if (m_preKey == GLFW_KEY_R)
                    m_pMagicCube->Move_R1();
                else if (m_preKey == GLFW_KEY_B)
                    m_pMagicCube->Move_B1();
                else if (m_preKey == GLFW_KEY_D)
                    m_pMagicCube->Move_D1();
                else if (m_preKey == GLFW_KEY_L)
                    m_pMagicCube->Move_L1();
                else if (m_preKey == GLFW_KEY_X)
                    m_pMagicCube->Move_X1();
                else if (m_preKey == GLFW_KEY_Y)
                    m_pMagicCube->Move_Y1();
                else if (m_preKey == GLFW_KEY_Z)
                    m_pMagicCube->Move_Z1();
                m_bKeyOn = false;
                m_preKey = GLFW_KEY_UNKNOWN;
            }
            return;
        case GLFW_KEY_2:
            if (true == m_bKeyOn)
            {
                if (m_preKey == GLFW_KEY_F)
                    m_pMagicCube->Move_F2();
                else if (m_preKey == GLFW_KEY_U)
                    m_pMagicCube->Move_U2();
                else if (m_preKey == GLFW_KEY_R)
                    m_pMagicCube->Move_R2();
                else if (m_preKey == GLFW_KEY_B)
                    m_pMagicCube->Move_B2();
                else if (m_preKey == GLFW_KEY_D)
                    m_pMagicCube->Move_D2();
                else if (m_preKey == GLFW_KEY_L)
                    m_pMagicCube->Move_L2();
                else if (m_preKey == GLFW_KEY_X)
                    m_pMagicCube->Move_X2();
                else if (m_preKey == GLFW_KEY_Y)
                    m_pMagicCube->Move_Y2();
                else if (m_preKey == GLFW_KEY_Z)
                    m_pMagicCube->Move_Z2();
                m_bKeyOn = false;
                m_preKey = GLFW_KEY_UNKNOWN;
            }
            return;
        case GLFW_KEY_3:
            if (true == m_bKeyOn)
            {
                if (m_preKey == GLFW_KEY_F)
                    m_pMagicCube->Move_F3();
                else if (m_preKey == GLFW_KEY_U)
                    m_pMagicCube->Move_U3();
                else if (m_preKey == GLFW_KEY_R)
                    m_pMagicCube->Move_R3();
                else if (m_preKey == GLFW_KEY_B)
                    m_pMagicCube->Move_B3();
                else if (m_preKey == GLFW_KEY_D)
                    m_pMagicCube->Move_D3();
                else if (m_preKey == GLFW_KEY_L)
                    m_pMagicCube->Move_L3();
                else if (m_preKey == GLFW_KEY_X)
                    m_pMagicCube->Move_X3();
                else if (m_preKey == GLFW_KEY_Y)
                    m_pMagicCube->Move_Y3();
                else if (m_preKey == GLFW_KEY_Z)
                    m_pMagicCube->Move_Z3();
                m_bKeyOn = false;
                m_preKey = GLFW_KEY_UNKNOWN;
            }
            return;
        case GLFW_KEY_0:
            m_pMagicCube->RandomShuffle();
            return;
        default:
            return;
        }
    }
}