/*************************************************
* Name : Window.cpp
* Purpose : Source for Window
* Date : 2020-11-09
* ************************************************/

#include "Window.h"
#include "Logger.h"
#include <sstream> // oss
#include "resource.h" // for window icon

/*
* Window::Exception
*/

Window::Exception::Exception(int line, const char* file, HRESULT hr)
	: CustomException(line, file), hr(hr) {}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl;
	oss << "[Error Code] " << GetErrorCode() << std::endl;
	oss << "[Description] " << GetErrorString() << std::endl;
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr)
{
	char* messageBuffer = nullptr;
	DWORD messageLength =
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER
			| FORMAT_MESSAGE_FROM_SYSTEM
			| FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&messageBuffer), 0, nullptr);

	if (messageLength == 0)
	{
		return "Unidentified error code";
	}
	else
	{
		std::string errorString = messageBuffer;
		LocalFree(messageBuffer);
		return errorString;
	}
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}

/*
* Window
*/

Window::Window(const wchar_t* winName, int width, int height)
	: windowName(winName), width(width), height(height)
{
	if (Initialize(windowName) == false)
	{
		Logger::GetLogger().LogError("Window Creation Failed");
		UnregisterClass(windowClassName, hInstance);
		throw WND_EXCEPT(GetLastError());
	}
}

Window::~Window()
{
	UnregisterClass(windowClassName, hInstance);
}

bool Window::Initialize(const wchar_t* winName) noexcept
{
	// register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = windowClassName;
	wc.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	RegisterClassEx(&wc);

	// create window instance.
	windowHandle = CreateWindowEx(0, windowClassName, winName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, this);

	if (windowHandle == nullptr)
	{
		return false;
	}

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
	case WM_KILLFOCUS:
		keyboard.ClearStates(); // clear states when lose focus
		break;
	/* Keyboard Messages */
	case WM_KEYDOWN: // keydown
	case WM_SYSKEYDOWN: // to detect ALT key
		keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:  // character key input, distinguish lower/uppercase depending state of shift.
		keyboard.OnChar(static_cast<unsigned char>(wParam));
		SetWindowText(hWnd, title.c_str());
		break;
	case WM_LBUTTONDOWN:
		POINTS mousePos = MAKEPOINTS(lParam);
		SetWindowText(hWnd, (L"x : " + std::to_wstring(mousePos.x) + L", y : " + std::to_wstring(mousePos.y)).c_str());
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}