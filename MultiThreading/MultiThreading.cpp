//Header Files 
#include <windows.h>

//Global Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM,LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;
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
	
	//Craete window
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
	
	//Message loop
	while (GetMessage(&msg, NULL, 0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
	TCHAR str[255];
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;	
	switch(iMsg)
	{
	case WM_CREATE:
		wsprintf(str,TEXT("WM_CREATE ARRIVED"));
		MessageBox(hwnd,str,TEXT("MESSAGE"),MB_OK);
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0,NULL);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(str,TEXT("RigthButton Click"));	
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	HDC hdc;
	long int i;
	TCHAR str[255];
	hdc = GetDC((HWND)param);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc, RGB(0,255,0));
	for(i = 0; i < 42947295; i++)
	{
		wsprintf(str, TEXT("ThreadOne --> IncreasingOrder %ld"),i);
		TextOut(hdc, 5, 5, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	HDC hdc;
	long int i;
	TCHAR str[255];
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for(i = 42947295; i > 0 ; i--)
	{
		wsprintf(str, TEXT("ThreadTwo --> DecreadingOrder %ld"),i);
		TextOut(hdc, 5, 20, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}
		
	
