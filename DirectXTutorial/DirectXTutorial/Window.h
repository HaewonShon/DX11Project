/*************************************************
* Name : Window.h
* Purpose : Header for Window
* Date : 2020-11-09
* ************************************************/
#pragma once

#include <Windows.h>
#include <string>
#include "CustomException.h"
#include "Keyboard.h"

class Window
{
public:
	class Exception : public CustomException
	{
	public:
		Exception(int line, const char* file, HRESULT hr);
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr);
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
	
public:
	Window(const wchar_t* windowName, int width, int height);
	~Window();
	inline LPCWSTR GetName() noexcept { return windowClassName; }
	inline HINSTANCE GetHandle() noexcept { return hInstance; }
	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

private:
	bool Initialize(const wchar_t* windowName) noexcept;
	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


private:
	const LPCWSTR windowClassName = L"DirectX tutorial Engine";
	const LPCWSTR windowName;
	HINSTANCE hInstance;
	HWND windowHandle;
	int width;
	int height;

public:
	Keyboard keyboard;

private:
	//prevent copy/assignment to this class
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

// macro for window exception
#define WND_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)