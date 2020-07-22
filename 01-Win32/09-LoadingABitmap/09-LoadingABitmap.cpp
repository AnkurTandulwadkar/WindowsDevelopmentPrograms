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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

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
	HBITMAP hBitmap;
	HDC hdc;
	HDC hdcMem;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bitmap;
	static HINSTANCE hInstance;

	switch (iMsg)
	{
	case WM_CREATE:
		hInstance = GetModuleHandle(NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
		hdcMem = CreateCompatibleDC(NULL);
		SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		DeleteObject(hBitmap);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}