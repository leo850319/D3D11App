#include "Window.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() : hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wcStruct = { 0 };
	wcStruct.cbSize = sizeof(wcStruct);
	wcStruct.style = CS_OWNDC | CS_DBLCLKS;
	wcStruct.lpfnWndProc = HandelMsgSetUp;
	wcStruct.cbClsExtra = 0;
	wcStruct.cbWndExtra = 0;
	wcStruct.hInstance = hInstance;
	wcStruct.hIcon = nullptr;
	wcStruct.hCursor = nullptr;
	wcStruct.hbrBackground = CreateSolidBrush(COLOR_WINDOW);
	wcStruct.lpszMenuName = nullptr;
	wcStruct.lpszClassName = className;
	wcStruct.hIconSm = nullptr;

	RegisterClassEx(&wcStruct);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(className, hInstance);
}

Window::Window(size_t width, size_t height, LPCSTR wndName) : width(width), height(height)
{
	RECT rt = { 0 };
	rt.left = 20;
	rt.top = 20;
	rt.right = rt.left + width;
	rt.bottom = rt.top + height;

	// specify window style
	LONG ws = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	AdjustWindowRect(&rt, ws, false);
	hWnd = CreateWindow(WindowClass::GetName(),
					wndName, ws, CW_USEDEFAULT,
					CW_USEDEFAULT, rt.right - rt.left,
					rt.bottom - rt.top, nullptr, nullptr,
					WindowClass::GetInstance(), this);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::Show()
{
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}
