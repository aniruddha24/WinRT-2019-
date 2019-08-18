//Header files 
#include <windows.h>
#include "MyMath.h"

//gloabal function declation
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	//initialization of WNDCLASSEX
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

	//register above class 
	RegisterClassEx(&wndclass);

	//Create Window
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
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hDll = NULL;
	typedef int(*MakeSquare)(int);
	MakeSquare pfn;
	int num = 5, square;
	TCHAR str[255];
	//code 
	switch (iMsg)
	{
	case WM_CREATE:
		hDll = LoadLibrary(TEXT("MyMath.dll"));
		if (NULL == hDll)
		{
			wsprintf(str, TEXT("LoadLibrary Fail DLL Missing"));
			MessageBox(hwnd, str, TEXT("Error Message"), MB_OK);
			DestroyWindow(hwnd);
		}
		pfn = (MakeSquare)GetProcAddress(hDll,"MakeSquare");
		if (NULL == pfn)
		{
			wsprintf(str, TEXT("Function Not Found "));
			MessageBox(hwnd, str, TEXT("Error Message"), MB_OK);
			DestroyWindow(hwnd);
		}
		square = pfn(num);
		wsprintf(str, TEXT("Square of %d is %d"), num, square);
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		FreeLibrary(hDll);
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


