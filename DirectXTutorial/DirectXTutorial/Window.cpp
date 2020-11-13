/*************************************************
* Name : Window.cpp
* Purpose : Source for Window
* Date : 2020-11-09
* ************************************************/

#include <iostream>
#include <Windows.h>
#include "Window.h"
#include "Logger.h"

Window::Window(const char* windowName, int width, int height) noexcept
	: windowName(windowName), width(width), height(height)
{
	if (Initialize() == false)
	{
		Logger::GetLogger().LogError("Window Creation Failed");
		UnregisterClass(windowClassName, hInstance);
		exit(-1);
	}
}

Window::~Window()
{
	UnregisterClass(windowClassName, hInstance);
}

bool Window::Initialize() noexcept
{
	// register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = windowClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// create window instance.
	windowHandle = CreateWindowEx(0, windowClassName, L"Hard-coded window..",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, this);

	// show the window
	ShowWindow(windowHandle, SW_SHOW);

	return true;
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// tutoral [window framework] 6
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		// Set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// Set message proc to normal(non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// retrieve ptr to window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	static std::wstring title;
	switch (msg)
	{
	case WM_CLOSE: // window message
		PostQuitMessage(0);
		return 0; // do not anything to destroy window(since destructor is called)
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
		SetWindowText(hWnd, (L"x : " + std::to_wstring(mousePos.x) + L", y : " + std::to_wstring(mousePos.y)).c_str());
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}