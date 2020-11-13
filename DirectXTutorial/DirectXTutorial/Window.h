/*************************************************
* Name : Window.h
* Purpose : Header for Window
* Date : 2020-11-09
* ************************************************/
#pragma once

#include <Windows.h>
#include <string>

class Window
{
public:
	Window(const char* windowName, int width, int height) noexcept;
	~Window();
	inline LPCWSTR GetName() noexcept { return windowClassName; }
	inline HINSTANCE GetHandle() noexcept { return hInstance; }
	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

private:
	bool Initialize() noexcept;
	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


private:
	const LPCWSTR windowClassName = L"DirectX tutorial Engine";
	const char* windowName;
	HINSTANCE hInstance;
	HWND windowHandle;
	int width;
	int height;

private:
	//prevent copy/assignment to this class
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};
