#pragma once

#include "Meta.h"
#include "vmath.h"

using namespace vmath;

#define LEN 2.05f

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
	void Draw(mat4 projection_matrix);
	//void Draw(mat4 projection_matrix, mat4 model_matrix);

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

private:
	static bool s_bProgramInited;
	static GLuint s_magicCubeProgram;	// all MagicCube object share one program;

	CubeUnit* pCubes_;
};

class MagicCubeMeta : public Meta
{
public:
	MagicCubeMeta();
	~MagicCubeMeta();

	void start(void);
	void render(void);
	void shutdown(void);

private:

	MagicCube* m_pMagicCube;
};