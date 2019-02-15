#pragma once

#include "JuWindows.h"

class Window
{
private:
	class WindowClass
	{
	public:
		static LPCSTR GetName() noexcept { return className; }
		static HINSTANCE GetInstance() noexcept { return wndClass.hInstance; }

	private:
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

	private:
		static constexpr LPCSTR className = "Ju Window Class Name";
		static WindowClass wndClass;
		HINSTANCE hInstance;
	};
public:
	Window() = delete;
	Window(size_t width, size_t height, LPCSTR wndName);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

public:
	void Show();

private:
	static LRESULT CALLBACK HandelMsgSetUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	size_t width;
	size_t height;
	HWND hWnd;
};