//Header files 
#include <windows.h>

//gloabal function declartion
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM,LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrecInstance,LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	
	//code 
	//iniralization of WNDCLASSEX
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
	
	//register aboce class 
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
	//code
	HDC hdc;
	TEXTMETRIC tm;
	static int cyChar;
	int i , X , Y;
	PAINTSTRUCT ps;
	RECT rc;
	char *str[] = {"India is my country.","All Indians are my Brothers and Sisters.","I love my country and","I am proud of its rich and varied heritage.","I shall always strive to be worthy of it.","I shall give my parents,","teachers and all elders respect","and treat everyone with courtesy.","To my country and my people,","I pledge my devotion.","In their well being and prosperity alone,","lies my happiness."};
	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &tm);
			ReleaseDC(hwnd,hdc);
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			break;	
		case WM_PAINT:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			X= rc.right/2;
			Y =rc.bottom/2;
			SetBkColor(hdc,RGB(0,0,0));
			for(i = 0; i  <=11; i++)
			{
				if( i < 4)
				{
					SetTextColor(hdc,RGB(255,200,0));
				}
				else if(i < 8)
				{
					SetTextColor(hdc,RGB(255,255,255));
				
				}
				else 
				{
					SetTextColor(hdc,RGB(0,255,0));
				}
				TextOut(hdc, X, Y, str[i],strlen(str[i]));
			 	Y = Y + cyChar;
			} 
			EndPaint(hwnd, &ps);
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
	



