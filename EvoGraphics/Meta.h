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

	virtual void start(void);
	virtual void render(void);
	virtual void shutdown(void);

	void SetMetaTime(double passedTime);

	double m_metaPassedTime = 0.0f;
};
