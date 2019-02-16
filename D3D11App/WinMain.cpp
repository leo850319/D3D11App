#include "JuWindows.h"
#include "Window.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, INT nCmdShow)
{
	Window window(1280, 720, "My D3D11");

	MSG msg;
	BOOL bResult;

	while (bResult = GetMessage(&msg, window.GetHandle(), 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (bResult == -1)
		return -1;

	return msg.wParam;
}