#include<Windows.h>

#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDialogProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE ghInstance;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX	wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	HMENU hMenu;
	ghInstance = hInstance;
	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(MYMENU));

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
		hMenu,
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
	static int idColor[] = {WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH, DKGRAY_BRUSH, BLACK_BRUSH};
	HBRUSH hBrush;

	switch (iMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_WHITE:
		case IDM_LTGRAY:
		case IDM_GRAY:
		case IDM_DKGRAY:
		case IDM_BLACK:
			hBrush = (HBRUSH)GetStockObject(idColor[LOWORD(wParam) - IDM_WHITE]);
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)hBrush);
			InvalidateRect(hwnd, NULL, true);
			break;

		case IDM_APP_ABOUT:
			DialogBox(ghInstance, TEXT("about"), hwnd, (DLGPROC)AboutDialogProc);

			break;
		}
		break;
		
	

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK AboutDialogProc(HWND hDlg, UINT iMsg, WPARAM wparam, LPARAM lparam) {

	switch (iMsg) {
	case WM_INITDIALOG:
		return true;

	case WM_COMMAND:
		switch (LOWORD(wparam)) {

		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, false);
			return true;
		}
		break;
	}

	return false;

}
