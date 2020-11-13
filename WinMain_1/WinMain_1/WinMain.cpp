#include <Windows.h>
#include <string>

//static bool isRunning = true;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/******************************************************************
* WinMain 
* - Entry for the window program.
* 
* HINSTANCE hInstance : hold info about program.
* HINSTANCE hPrevInstance : hold info
* LPSTR lpCmdLine : get command line as a string?
* int nCmdShow : how window should show up
********************************************************************/
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const LPCWSTR className = L"blank_window";

	// register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc); 

	// create window instance.
	HWND windowHandle = CreateWindowEx(0, className, L"Hard-coded window..", 
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

	// show the window
	ShowWindow(windowHandle, SW_SHOW);

	// message pump
	MSG message;
	BOOL messageResult;

	// return of GetMessage 0 - exit, -1 - error
	while ((messageResult = GetMessage(&message, nullptr, 0, 0)) > 0) // message - such as window event.. 
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	if (messageResult == -1)
	{
		return -1;
	}
	else
	{
		return message.wParam;
	}

	return 0;
} 

/******************************
* LRESULT CALLBACK WndProc
* - custom window procedure
********************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static std::wstring title;
	switch (msg)
	{
	case WM_CLOSE: // window message
		PostQuitMessage(12);
		break;
	case WM_KEYDOWN: // keydown
		if (wParam == 'F')
		{
			// set window name
			SetWindowText(hWnd, L"respond to F");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, L"zz");
		}
		break;
	case WM_CHAR:  // character key input, distinguish lower/uppercase depending state of shift.
		title.push_back((char)wParam);
		SetWindowText(hWnd, title.c_str());
		break;
	case WM_LBUTTONDOWN:
		POINTS mousePos = MAKEPOINTS(lParam);
		SetWindowText(hWnd, ( L"x : " + std::to_wstring(mousePos.x) + L", y : " + std::to_wstring(mousePos.y) ).c_str());
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}