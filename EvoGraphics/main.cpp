#include <Windows.h>
#include <iostream>
#include "Manager.h"
#include "Meta.h"

#include "Draw.cpp"		// for test

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{               
	/*
	singlepoint_app * app = new singlepoint_app;
	app->run(app);                                  
	delete app;
	*/

	GraphicsManager* pManager = GraphicsManager::GetInstance();
	if (!pManager)
	{
		return -1;
	}

	Meta newMeta;
	pManager->SetMeta(&newMeta);

	pManager->init();
	pManager->start();
	pManager->render();
	pManager->shutdown();

	return 0;                                       
}