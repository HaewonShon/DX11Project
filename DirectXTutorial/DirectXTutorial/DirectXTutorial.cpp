/*************************************************
* Name : main.cpp
* Purpose : WinMain Entry
* Date : 2020-11-09
* ************************************************/

#include "Window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window("noob window", 800, 600);
	Window window2("noob2", 100, 100);

	MSG msg;
	BOOL gResult;
	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	return 0;
}