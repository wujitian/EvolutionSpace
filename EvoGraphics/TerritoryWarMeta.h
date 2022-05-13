#pragma once

#include "Meta.h"

class TerritoryWarMeta : public Meta
{
public:
	TerritoryWarMeta();
	~TerritoryWarMeta();

	void start(void);
	void render(void);
	void shutdown(void);

private:
	GLuint program;     // temp
	GLuint vao;         // temp
};