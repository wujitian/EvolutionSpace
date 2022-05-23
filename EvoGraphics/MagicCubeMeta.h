#pragma once

#include "Meta.h"
#include "vmath.h"

using namespace vmath;

#define LEN 2.05f
#define THRESHOLD 0.01f
#define STRIDE 1.0f

#define RED vec3(1.0, 0.0, 0.0)
#define GREEN vec3(0.0, 1.0, 0.0)
#define BLUE vec3(0.0, 0.0, 1.0)
#define YELLOW vec3(1.0, 1.0, 0.0)
#define PINK vec3(1.0, 0.0, 1.0)
#define ORANGE vec3(1.0, 0.75, 0.5)
#define WHITE vec3(1.0, 1.0, 1.0)
#define BLACK vec3(0.2, 0.2, 0.2)

class CubeBasic
{
public:
	CubeBasic(float x = 0.0, float y = 0.0, float z = 0.0,
		vec3 color_front = RED, vec3 color_back = ORANGE,
		vec3 color_top = YELLOW, vec3 color_bottom = WHITE,
		vec3 color_left = BLUE, vec3 color_right = GREEN);
	~CubeBasic();

	void SetCenterCoords(float x = 0.0, float y = 0.0, float z = 0.0);
	void SetColors(vec3 color_front = RED, vec3 color_back = ORANGE,
		vec3 color_top = YELLOW, vec3 color_bottom = WHITE,
		vec3 color_left = BLUE, vec3 color_right = GREEN);
	void Init(GLuint program);
	void Draw(mat4 projection_matrix, mat4 model_matrix);

private:
	float x_ = 0.0;
	float y_ = 0.0;
	float z_ = 0.0;

	vec3 color_front_;
	vec3 color_back_;
	vec3 color_top_;
	vec3 color_bottom_;
	vec3 color_left_;
	vec3 color_right_;

	GLuint vao_;
	GLuint vbo_;
	GLuint program_;
	GLint model_matrix_;
	GLint projection_matrix_;
};

class CubeUnit
{
public:
	CubeUnit();
	~CubeUnit();

	void SetCenterCoords(float x, float y, float z);
	void SetColors(vmath::vec3 front, vmath::vec3 back, vmath::vec3 top, vmath::vec3 bottom,
		vmath::vec3 left, vmath::vec3 right);
	void Init(GLuint program);
	void MatrixInit(void);
	void SetMove(float angle_x, float angle_y, float angle_z);
	bool IsRunning(void);
	void Draw(void);

private:
	CubeBasic m_cube;
	GLuint m_program;
	vec3 m_position;
	vec3 m_colorFront;
	vec3 m_colorBack;
	vec3 m_colorTop;
	vec3 m_colorBottom;
	vec3 m_colorLeft;
	vec3 m_colorRight;
	vmath::mat4 m_projection_matrix;
	vmath::mat4 m_base_model_matrix;
	vmath::mat4 m_angle_model_matrix;
	float m_var_angle_x = 0.0f;
	float m_var_angle_y = 0.0f;
	float m_var_angle_z = 0.0f;
	bool m_bRunning = false;
};

class MagicCube
{
public:
	MagicCube();
	~MagicCube();

	bool Init();
	bool Draw();

	static bool InitProgram();
	static bool DestoryProgram();	// when MagicCubeMeta destroy, need call this function to release program

	bool CanMove(void);

	//Move Funciton
	void Move_F1(void);

private:
	static bool s_bProgramInited;
	static GLuint s_magicCubeProgram;	// all MagicCube object share one program;

	int cubeIds_[27];
	CubeUnit* pCubes_;

	void SwithID_ClockWise(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2);
};

class MagicCubeMeta : public Meta
{
public:
	MagicCubeMeta();
	~MagicCubeMeta();

	void start(void);
	void render(void);
	void shutdown(void);

	void WindowKey(int key, int scancode, int action, int mods);

private:
	MagicCube* m_pMagicCube;

	// Key Press
	bool m_bKeyOn;
	GLuint m_preKey;
};