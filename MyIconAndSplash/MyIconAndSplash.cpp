//Header 
#include <windows.h>
#include "MyIconAndSplash.h"

//golobl function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM,LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrecInstance, LPSTR lpszCmdLine,int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	
	//code
	//intialzation of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = 0;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	
	//register above class
	RegisterClassEx(&wndclass);
	
	//create window
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

	//message loop
	while(GetMessage(&msg, NULL, 0 , 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	BITMAP bitmap;
	RECT rc;
	static HINSTANCE hIns;
	static HDC hdc , hdctemp;
	PAINTSTRUCT ps;
	static HBITMAP hbitmap;
	
	//code
	switch(iMsg)
	{
		case WM_DESTROY:
			DeleteObject(hbitmap);
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			hbitmap = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(MYBITMAP));
			break;
		case WM_PAINT:
			hdc = BeginPaint(hwnd ,&ps);
			GetClientRect(hwnd, &rc);				
			hdctemp  = CreateCompatibleDC(hdc);
			SelectObject(hdctemp,hbitmap);
			GetObject(hbitmap, sizeof(BITMAP), &bitmap);
			BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdctemp, 0 , 0, SRCCOPY);
			DeleteDC(hdctemp);
			EndPaint(hwnd,&ps);
			break;
			
			
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
	
