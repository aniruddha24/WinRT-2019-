//Header File
#include <windows.h>

//golabal decalaration of function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrecInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//varible declartion
	WNDCLASSEX  wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	//intialzation of WNDCLASSEX
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
	
	//messasge loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local varaible declaraion and intialization
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[] = TEXT("Hellow World!!!");
	TCHAR str1[255];
	RECT rc;

	//code
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		wsprintf(str1, TEXT("Message"));
		MessageBox(hwnd, str1, TEXT("WM_CREATE is Arrived"),MB_OK);
	case WM_PAINT:
		//Get Changing Rectangle
		GetClientRect(hwnd, &rc);
		//Call Specialist
		//i.e Create the HDC
		hdc = BeginPaint(hwnd, &ps);
		//Set text colour
		SetTextColor(hdc, RGB(0, 255, 0));
		//Set BackGound Color
		SetBkColor(hdc, RGB(0, 0, 0));
		//Draw the Actual Text
		DrawText(hdc, str, -1, &rc ,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//Sent back the spcialist and stop Painting
		EndPaint(hwnd, &ps);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

