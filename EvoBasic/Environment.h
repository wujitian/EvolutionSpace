#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

class Environment
{
public:
	Environment() { srand(time(NULL)); };
	~Environment() {};
};
