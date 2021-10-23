#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

class Environment
{
public:
	Environment() { srand((uint32_t)time(NULL)); };
	~Environment() {};
};
