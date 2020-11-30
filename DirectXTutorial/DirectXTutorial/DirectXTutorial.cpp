/*************************************************
* Name : DirectXTutorial.cpp
* Purpose : WinMain Entry
* Date : 2020-11-09
* ************************************************/

#include "Window.h"
#include "CustomException.h"
#include "Helper.h"

/* WinMain */
int CALLBACK WinMain(
	[[maybe_unused]] HINSTANCE hInstance, 
	[[maybe_unused]] HINSTANCE hPrevInstance,
	[[maybe_unused]] LPSTR lpCmdLine, 
	[[maybe_unused]] int nCmdShow)
{
	try {
		Window window(L"noob window", 800, 600);

		MSG msg;
		BOOL gResult = GetMessage(&msg, nullptr, 0, 0);
		while (gResult > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (window.keyboard.IsKeyPressed(VK_ESCAPE))
			{
				MessageBox(nullptr, L"lol", L"escape pressed", MB_OK | MB_ICONEXCLAMATION);
			}
			gResult = GetMessage(&msg, nullptr, 0, 0);
		}

	if (gResult == -1)
	{
		return -1;
	}
	return 0;

	}
	catch (const CustomException& e)
	{
		MessageBox(nullptr, stringTowstring(std::string(e.what())).c_str(), stringTowstring(std::string(e.GetType())).c_str(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (std::exception& e)
	{
		MessageBox(nullptr, stringTowstring(std::string(e.what())).c_str(), L"Standard exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1; // after exception catched
}