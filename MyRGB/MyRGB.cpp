//Headers
#include <windows.h>

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrecInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	
	//code 
	//Initialization of WNDCLASSEX
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
	wndclass.lpszMenuName = 0;
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
	
	//message loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int iPaintflag = 0 ;
	TCHAR str[255];
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	//local varailable declaration and Initilazation
	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			wsprintf(str,TEXT("Message"));
			MessageBox(hwnd, str, TEXT("WN_CREATE is Arrived"),MB_OK);
			break;	
		case WM_CHAR:
			switch(LOWORD(wParam))
			{
			case 'R':
			case 'r':
				iPaintflag = 1;
				InvalidateRect(hwnd,NULL,TRUE);//hwnd,&rc,TRUE
				break;
			case 'G':
			case 'g':
				iPaintflag = 2;
				InvalidateRect(hwnd,NULL,TRUE);
				break;
			case 'B':
			case 'b':
				iPaintflag = 3;
				InvalidateRect(hwnd,NULL,TRUE);
				break;
			case 'C':
			case 'c':
				iPaintflag = 4;
				InvalidateRect(hwnd,NULL,TRUE);	
				break;
			case 'M':
			case 'm':
				iPaintflag = 5;
				InvalidateRect(hwnd,NULL,TRUE);
				break;
			case 'Y':
			case 'y':
				iPaintflag = 6;
				InvalidateRect(hwnd,NULL,TRUE);
				break;
			case 'W':
			case 'w':
				iPaintflag = 7;
				InvalidateRect(hwnd,NULL,TRUE);
				break;
			case 'K':
			case 'k':
			default:
				iPaintflag = 8;
				InvalidateRect(hwnd,NULL,TRUE);
				break;	
			}
			break;
	
		case WM_PAINT:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			switch(iPaintflag)
			{
				case 0:
					hbrush = CreateSolidBrush(RGB(0,0,0));
					SelectObject(hdc , hbrush);
					FillRect(hdc, &rc,hbrush);
					break;
				case 1:
					hbrush = CreateSolidBrush(RGB(255,0,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rc, hbrush);
					break;
				case 2:
					hbrush = CreateSolidBrush(RGB(0,255,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rc, hbrush);
					break;
				case 3:
					hbrush = CreateSolidBrush(RGB(0,0,255));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rc, hbrush);
					break;
				case 4:
					hbrush = CreateSolidBrush(RGB(0,255,255));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rc, hbrush);
					break;
				case 5:
					hbrush = CreateSolidBrush(RGB(255,0,255));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rc, hbrush);
					break;
				case 6:
					hbrush = CreateSolidBrush(RGB(255,255,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc,&rc, hbrush);
					break;
				case 7:
					hbrush = CreateSolidBrush(RGB(255,128,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rc, hbrush);
					break;
				case 8:
				default:
					hbrush = CreateSolidBrush(RGB(0,0,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rc, hbrush);
					break;
			}
			EndPaint(hwnd,&ps);
			break;		
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}