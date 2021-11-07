#include <Windows.h>
#include <iostream>

#include "Draw.cpp"		// for test

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{                                                   
	singlepoint_app * app = new singlepoint_app;
	app->run(app);                                  
	delete app;                                     
	return 0;                                       
}