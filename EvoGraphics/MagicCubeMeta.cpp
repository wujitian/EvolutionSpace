#include "MagicCubeMeta.h"

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
    
    //model_matrix_ = glGetUniformLocation(program_, "model_matrix");
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

//void CubeBasic::Draw(mat4 projection_matrix, mat4 model_matrix)
void CubeBasic::Draw(mat4 projection_matrix)
{
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glUniformMatrix4fv(projection_matrix_, 1, GL_FALSE, projection_matrix);
    //glUniformMatrix4fv(model_matrix_, 1, GL_FALSE, model_matrix);

    //glDrawArrays(GL_TRIANGLES, 0, 36);
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
    //base_model_matrix = vmath::translate(0.0f, 0.0f, -10.0f);
    //angle_model_matrix = vmath::rotate(0.0f, vec3(0.0f, 0.0f, 1.0f));
}

void CubeUnit::Draw(void)
{
    /*
    bool bIn = false;
    if (var_angle_x > THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(STRIDE, vec3(1.0f, 0.0f, 0.0f)) * angle_model_matrix;
        var_angle_x -= STRIDE;
        bIn = true;
    }
    else if (var_angle_x < -THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(-STRIDE, vec3(1.0f, 0.0f, 0.0f)) * angle_model_matrix;
        var_angle_x += STRIDE;
        bIn = true;
    }

    if (var_angle_y > THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(STRIDE, vec3(0.0f, 1.0f, 0.0f)) * angle_model_matrix;
        var_angle_y -= STRIDE;
        bIn = true;
    }
    else if (var_angle_y < -THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(-STRIDE, vec3(0.0f, 1.0f, 0.0f)) * angle_model_matrix;
        var_angle_y += STRIDE;
        bIn = true;
    }

    if (var_angle_z > THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(STRIDE, vec3(0.0f, 0.0f, 1.0f)) * angle_model_matrix;
        var_angle_z -= STRIDE;
        bIn = true;
    }
    else if (var_angle_z < -THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(-STRIDE, vec3(0.0f, 0.0f, 1.0f)) * angle_model_matrix;
        var_angle_z += STRIDE;
        bIn = true;
    }
    
    if (false == bIn)
    {
        bRunning = false;
    }
    */
    //m_cube.Draw(projection_matrix, base_model_matrix * angle_model_matrix);
    m_cube.Draw(m_projection_matrix);
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
        "uniform mat4 projection_matrix;                                   \n"
        "                                                                  \n"
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
        "    gl_Position = projection_matrix * position;                   \n"
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
        //cubeIds_[i] = i;
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

/// <summary>
/// MagicCubeMeta class
/// </summary>

MagicCubeMeta::MagicCubeMeta()
{
    dprintf_i("[MagicCubeMeta] MagicCubeMeta create.");

    m_pMagicCube = nullptr;
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