#include<Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX	wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hBrush[8];
	static int iPaintFlag;
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;

	switch (iMsg)
	{
		
	case WM_CREATE:
		hBrush[0] = CreateSolidBrush(RGB(255,0,0));
		hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
		hBrush[2] = CreateSolidBrush(RGB(0, 0, 255));
		hBrush[3] = CreateSolidBrush(RGB(0, 255, 255));
		hBrush[4] = CreateSolidBrush(RGB(255, 0, 255));
		hBrush[5] = CreateSolidBrush(RGB(255, 255, 0));
		hBrush[6] = CreateSolidBrush(RGB(0, 0, 0));
		hBrush[7] = CreateSolidBrush(RGB(255, 255, 255));

		SetTimer(hwnd, MYTIMER, 1000, NULL);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MYTIMER);
		iPaintFlag++;

		if (iPaintFlag > 7)
			iPaintFlag = 0;

		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, MYTIMER, 1000, NULL);

		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, hBrush[iPaintFlag]);
		FillRect(hdc, &rc, hBrush[iPaintFlag]);
		EndPaint(hwnd, &ps);

		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}