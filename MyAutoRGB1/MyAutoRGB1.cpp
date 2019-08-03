//Headers 
#include <windows.h>
#define MYTIMER 100

//global funtion declaraiton
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM,LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	
	//code
	//initilization of WNDCLASS
	wndclass.cbSize = sizeof(WNDCLASSEX);	
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
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
	TCHAR str[255];
	HDC hdc;
	RECT rc ,rctemp;
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	static int iPaintflag = 0;
	static int rcright = 0; 	
	
	//code
	switch(iMsg)
	{
		case WM_CREATE:
			SetTimer(hwnd, MYTIMER, 2000, NULL);
			wsprintf(str,TEXT("WM_CREATE is Arrived"));
			MessageBox(hwnd,str,TEXT("Message"),MB_OK);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_TIMER:
			{
				KillTimer(hwnd, MYTIMER);
				iPaintflag = iPaintflag + 1;	
				if(iPaintflag < 10)
				{
					InvalidateRect(hwnd, NULL, FALSE);
				}
				else
				{
					InvalidateRect(hwnd, NULL, TRUE);
				}
				SetTimer(hwnd, MYTIMER, 2000, NULL);
			}
			break;
		case WM_PAINT:
			//Get changing rectang
			GetClientRect(hwnd,&rc);
			rctemp.left = rc.left + rcright;
			rctemp.right = (rc.right/10) + rcright;
			rctemp.top = rc.top;
			rctemp.bottom = rc.bottom;
			rcright = rctemp.right;
	
			//call specialist
			hdc = BeginPaint(hwnd, &ps);
				
			//code 
			switch(iPaintflag)
			{
				case 1:
					hbrush = CreateSolidBrush(RGB(255,0,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);
					break;
				case 2:
					hbrush = CreateSolidBrush(RGB(0,255,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);	
					break;
				case 3:
					hbrush = CreateSolidBrush(RGB(0,0,255));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);
					break;
				case 4:
					hbrush = CreateSolidBrush(RGB(0,255,255));
					SelectObject(hdc, hbrush);	
					FillRect(hdc, &rctemp, hbrush);
					break;
				case 5:
					hbrush = CreateSolidBrush(RGB(255,0,255));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);	
					break;
				case 6:
					hbrush = CreateSolidBrush(RGB(255,255,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);
					break;
				case 7:
					hbrush = CreateSolidBrush(RGB(255,128,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);
					break;
				case 8:
					hbrush = CreateSolidBrush(RGB(64,64,64));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);
					break;
				case 9:
					hbrush = CreateSolidBrush(RGB(128,128,128));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);
					break;
				case 10:
				default:
					hbrush = CreateSolidBrush(RGB(0,0,0));
					SelectObject(hdc, hbrush);
					FillRect(hdc, &rctemp, hbrush);	
					iPaintflag = 0;
					rcright = 0;
					break;					
				}
				EndPaint(hwnd, &ps);	
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

