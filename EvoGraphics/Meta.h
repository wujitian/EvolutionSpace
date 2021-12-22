#pragma once

#include "gl3w.h"
#include "glfw3.h"

#include <iostream>
#include <string.h>

#include "logger.h"

class Meta
{
public:
	Meta();
	~Meta();

	void start(void);
	void render(void);
	void shutdown(void);

private:
	GLuint program;     // temp
	GLuint vao;         // temp
};
