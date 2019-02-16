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
	wcStruct.hbrBackground = nullptr;
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

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT Window::HandelMsgSetUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* pWindow = reinterpret_cast<Window*>(cs->lpCreateParams);
		
		SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLong(hWnd, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(pWindow->HandelMsgThunk));

		return pWindow->HandelMsg(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::HandelMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* pWindow = reinterpret_cast<Window*>(GetWindowLong(hWnd, GWL_USERDATA));

	return pWindow->HandelMsg(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::HandelMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
