#pragma once

#include "Meta.h"

class CubeBasic
{
public:
	CubeBasic();
	~CubeBasic();
};

class CubeUnit
{
public:
	CubeUnit();
	~CubeUnit();
};

class MagicCube
{
public:
	MagicCube();
	~MagicCube();
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
	GLuint program;     // temp
	GLuint vao;         // temp
};