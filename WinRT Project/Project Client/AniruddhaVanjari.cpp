#include <windows.h>
#include <winuser.h>
#include "AniruddhaVanjari.h"
#include <CommCtrl.h>
#include "AniruddhaVanjariServer.h"

LRESULT CALLBACK WndProc(HWND , UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND,UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc1(HWND,UINT, WPARAM, LPARAM);
BOOL MyReadFile(HANDLE, char *, DWORD *);
BOOL ZeroStrCmp(char *);
//int DialogBox(HINSTANCE,LPCTSTR,HWND,DLGPROC);

HWND hwnd;

IWrite *pIWrite = NULL;
IRead *pIRead = NULL;

struct INPUT1
{
	char name[50];
	char address[50];
	int age,mstatus;
	int sal;
};
struct INPUT1 in;
struct INPUT1 ot;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

	WNDCLASSEX wndclass;
	//HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	HRESULT hr;
	hr = CoInitialize(NULL);
	if(hr)
	{
		MessageBox(NULL,TEXT("COM Library Can Not Be Initialized.\nProgram Will Now Exit."),
		TEXT("Program Error"),MB_OK);
		exit(0);
	}
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW|CS_VREDRAW;
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
	
	hwnd = CreateWindow(szAppName, TEXT("My Application"),WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	
	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return((int)msg.wParam);
}
void SafeInterfaceRelease(void);
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	
	BITMAP bitmap;
	RECT rc;
	static HINSTANCE hIns;
	static HDC hdc, hdctemp;
	PAINTSTRUCT ps;
	static HBITMAP hbitmap;
	HRESULT hr;
	static HINSTANCE hInst;
	switch(iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_CWriteRead,NULL,CLSCTX_INPROC_SERVER,IID_IWrite,(void **)&pIWrite);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("IWrite Interface Can Not Be Obtained"),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}
		hbitmap = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(MYBITMAP));
		//hInst = (HINSTANCE)GetWindowLong(hwnd,lParam);
		//hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hdctemp = CreateCompatibleDC(hdc);
		SelectObject(hdctemp,hbitmap);
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);
		StretchBlt(hdc, 0, 0,
		bitmap.bmWidth,
		bitmap.bmHeight,
		hdctemp, 0, 0, bitmap.bmWidth,
		bitmap.bmHeight,
		SRCCOPY);
		DeleteDC(hdctemp);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_SPACE:
			DialogBox(hInst,"DATAENTRY", hwnd, (DLGPROC)MyDlgProc);
			DestroyWindow(hwnd);
		break;
		}
		break;
	case WM_DESTROY:
		DeleteObject(hbitmap);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam,lParam));
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{	
	
	char str[255];
	char salrs[6],salps[3];
	char DataBuffer[BUFSIZE] = {};
	static HANDLE	hFile;
	static HINSTANCE hInst1;
	DWORD datawritten;
	HRESULT hr;
	switch(iMsg)	
	{
		case WM_INITDIALOG:
		//CoCreateInstance 
		
		hFile = CreateFile(".\\Data.txt",FILE_APPEND_DATA, FILE_SHARE_READ, NULL,OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile == INVALID_HANDLE_VALUE)
			{
				MessageBox(hwnd,TEXT("CreateFile Fail"),TEXT("Message"),MB_OK);
			}
		//hInst1 = (HINSTANCE)GetWindowLong(hwnd,lParam);
		//set focus in name Edit Box
		SetFocus(GetDlgItem(hDlg,ID_ETNAME));

		//keep married Radio Button Checked
		SendDlgItemMessage(hDlg, ID_RBMARRIED,BM_SETCHECK,1,0);
		

		return(TRUE);
		
		case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case ID_PBCONTINUE:
			CloseHandle(hFile);
			DialogBox(NULL,"SEARCHING", hwnd,(DLGPROC)MyDlgProc1);
			hFile = CreateFile(".\\Data.txt",FILE_APPEND_DATA, FILE_SHARE_READ, NULL,OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile == INVALID_HANDLE_VALUE)
			{
				MessageBox(hwnd,TEXT("CreateFile Fail"),TEXT("Message"),MB_OK);
			}
			break;
			
			case IDOK:
			{
				//Get the user-entered name
				GetDlgItemText(hDlg,ID_ETNAME,in.name,50);
				//MessageBox(hwnd,in.name,TEXT("Message"),MB_OK);
				//Get the User-enterd addess;
				GetDlgItemText(hDlg,ID_ETADDRESS,in.address,50);
				
				//Get the user-enter age 
				in.age = GetDlgItemInt(hDlg,ID_ETAGE,NULL,TRUE);
				//Get th user-enterd salary
				in.sal = GetDlgItemInt(hDlg,ID_ETSALRS,NULL,TRUE);
			
				//Get user-enterd marial status
				in.mstatus = SendDlgItemMessage(hDlg,ID_RBMARRIED,BM_GETCHECK,0,0);
				wsprintf(str,TEXT("%d"),in.mstatus);
				//MessageBox(hwnd,str,TEXT("Message"),MB_OK);
				if(in.mstatus)
					wsprintf(str,TEXT("Married"));
				else
					wsprintf(str,TEXT("Unmarried"));
				wsprintf(DataBuffer, TEXT("\n%s! %s! %d! %d! %s! "),in.name,in.address,in.age,in.sal,str);  
				
	
				//(HANDLE hFile,LPCVOID DataBuffer,DWORD,LPDWORD DataBuffer,
			
				if(ZeroStrCmp(in.name))
				{	
					MessageBox(hwnd,TEXT("Fill Inforamtion Correctly"),TEXT("ERROR Message"),MB_OK);
				
				}
				else
				{
					pIWrite->NiceWrite(hFile, DataBuffer,&datawritten);
					MessageBox(hwnd,TEXT("Inforamtion Stored..."),TEXT("Succes Message"),MB_OK);
				}
			}
			break;

			case IDCANCEL:
			pIWrite->Release();
			pIWrite = NULL;
			CloseHandle(hFile);
			EndDialog(hDlg,0);
			break;
		}
		
		return(TRUE);
	}
	return(FALSE);
}

BOOL CALLBACK MyDlgProc1(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	
	static int loop1, flag = 1,size = 0;
	static char entername[50];
	static int n,i ,space ;
	static char age[10] , salary[20], status[10];
	static TCHAR str[255]= {};
	DWORD dwBytesRead;
	char DataBuffer[BUFSIZE] = {};
	static HANDLE hReadFile;
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	static HWND hwndListView;
	InitCommonControlsEx(&icex);
	char salrs[6],salps[3];
	//struct INPUT1 in;
	static HINSTANCE hInst2;
	int iCol;
	LVCOLUMNA lvc;
	static LVITEM lvI;
	//TCHAR szText[10] = TEXT("NAME");
	static int index;
	static int Subitem;
	HRESULT hr;
	switch(iMsg)
	{
		
		case WM_INITDIALOG:
		{
			hr = pIWrite->QueryInterface(IID_IRead,(void **)&pIRead);
			if(hr)
			{
				MessageBox(hwnd, TEXT("hr fail pISubtract"),TEXT("Message"),MB_OK);
			}
			InitCommonControlsEx(&icex);
			RECT rcClient;
			GetClientRect(hDlg,&rcClient);
			hwndListView = CreateWindow(WC_LISTVIEW,
					TEXT(""),
						WS_CHILD | LVS_REPORT | WS_VISIBLE,
						20,90,
						400,
						300,
						hDlg,NULL,
						NULL,
						NULL);
			//List View Coloms Header
			for (iCol = 0; iCol < 5 ; iCol++)
			{
				lvc.mask = LVCF_WIDTH | LVCF_TEXT ;
				lvc.iSubItem = iCol;
				//lvc.pszText = (LPWSTR)szText;
				switch(iCol)
				{
					case 0:
						lvc.pszText = (LPSTR)"NAME";
						break;
					case 1:
						lvc.pszText = (LPSTR)"Address";
						break;
					case 2:
						lvc.pszText = (LPSTR)"AGE";
						break;
					case 3:
						lvc.pszText = (LPSTR)"SALARY";
						break;
					case 4:
						lvc.pszText = (LPSTR)"MARAGE S.";
						break;
				}
				lvc.cx = 100;
				lvc.cchTextMax = 10;
				
				if( iCol < 2)
					lvc.fmt = LVCFMT_LEFT;
				else
					lvc.fmt = LVCFMT_RIGHT;
				//LoadString(NULL,IDS_FIRSTCOLUMNS + iCol,szText,sizeof(szText)/sizeof(szText[0]));

				ListView_InsertColumn(hwndListView,iCol, &lvc);
				
				
			}
			
			
			//CloseHandle(hReadFile);
			//hInst2 = (HINSTANCE)GetWindowLong(hwnd,lParam);
			//set focus in name Edit Box
			SetFocus(GetDlgItem(hDlg,ID_ETNAME));
			return(TRUE);
		}
		break;
		case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case ID_CANCEL:
			pIRead->Release();
			pIRead = NULL;
			CloseHandle(hReadFile);
			EndDialog(hDlg,0);
			break;
			

			case ID_PBSEARCH:
			{
			ListView_DeleteAllItems(hwndListView);
			hReadFile = CreateFile(".\\Data.txt",GENERIC_READ, 0, NULL, OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL,NULL);
			if(hReadFile == INVALID_HANDLE_VALUE)
			{
				MessageBox(hwnd,TEXT("CreateFIle Read Fail"),TEXT("Message"),MB_OK);
			}
			//pISubtract->SubtractionOfTwoIntegers(hReadFile,DataBuffer,&dwBytesRead);
			//wsprintf(str,"%s= %d",DataBuffer,dwBytesRead);
			//MessageBox(hwnd,str,TEXT("Message"),MB_OK);
			//Read File Operation
			index = 0;
			TCHAR STR1[255] = {};
			//SUPER Read >>>>>>>>>>>>>>>>
			while( MyReadFile(hReadFile,DataBuffer,&dwBytesRead) && dwBytesRead > 0)
			{
			
				wsprintf(str,TEXT("%s"),DataBuffer);
				n = 0;
				i = 0;
				space = 0;
				size = 0;
				flag = 0;
				//MessageBox(hwnd,str,TEXT("Message"),MB_OK);
				memset(&ot, 0, sizeof(ot));
				memset(&salary,0,sizeof(salary));
				memset(&age,0,sizeof(salary));
				
				while(n <= sizeof(str))
				{
					if(space == 0)
					{	//Name
						if(str[n] != '!')
						{
							ot.name[i] = str[n];
							size = size + 1;
							i = i + 1;
						}
						else 
						{
							i = 0;
							space = 1;
							n = n + 1;
						}
					}
					//Address
					if(space == 1)
					{
						if(str[n] != '!')
						{
							ot.address[i] = str[n];
							i = i + 1;
						}
						else
						{
							i = 0;
							space = 2;
							n = n + 1;
						}
					}
					//Age
					if(space == 2)
					{
						if(str[n] != '!')
						{
							age[i] = str[n];
							i = i + 1;
						}
						else
						{
							i = 0;
							space = 3;
							n = n + 1;
						}
					}
					//Salary
					if(space == 3)
					{
						if(str[n] != '!')
						{
							salary[i] = str[n];
							i = i + 1;
						}
						else
						{
							i = 0;
							space = 4;	
							n = n + 1;
						}
					}	
					//Marrage Status
					if(space == 4)
					{
						if(str[n] != '!')
						{
							status[i] = str[n];
							i = i + 1;
						}
						else
						{
							break;
						}
					}
					n = n + 1;
				}
				GetDlgItemText(hDlg,ID_ETNAME,entername,50);
				wsprintf(str,TEXT("%s"),ot.name);

				for( loop1 = 0; loop1 < size; loop1++)
				{
					if(ot.name[loop1+1] == entername[loop1])
						flag = flag + 1;
					//wsprintf(str,TEXT("%c %c %d"),ot.name[loop1+1],entername[loop1], loop1);
					//MessageBox(hwnd,str,TEXT("MESSAGE"),MB_OK);
				}
				//wsprintf(str,TEXT("flag:-%d size:-%d"),flag,size);
				//MessageBox(hwnd,str,TEXT("MESSAGE"),MB_OK);
				if(flag !=size)
				{	flag = 0;
					continue;
				}
				flag = 0;
				memset(&lvI, 1, sizeof(LVITEM));////// khup khup khup khup mahatvacha aahe he..............!!!!!!!!!!!!!!!
				//SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
				lvI.mask = LVIF_TEXT;// | LVIF_COLFMT | LVIF_COLUMNS;
			
				//lvI.pszText = (LPSTR)"NAME";
				//lvI.iItem = 0;
				//lvI.stateMask = 0;
				//lvI.state = 0;
				lvI.iSubItem = 0;
			
	
				lvI.iItem = index;
				for(int SubItem = 0; SubItem <5;SubItem++)
				{	
					lvI.iSubItem = SubItem;
					switch(lvI.iSubItem)
					{
					case 0:
						lvI.pszText = (LPSTR)ot.name;
						ListView_InsertItem(hwndListView, &lvI);
						break;
					case 1:
						lvI.pszText = (LPSTR)ot.address;
						SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						break;
					case 2:
						lvI.pszText = (LPSTR)age;
						SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						break;
					case 3:
						lvI.pszText = (LPSTR)salary;
						SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						break;
					case 4:
						lvI.pszText = (LPSTR)status;
						SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						break;
					}
					//SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
				} 
			
			index = index + 1;	
			//MessageBox(hwnd, age,TEXT("Message1"),MB_OK);
			
			}
			//End of ReadOperation
			CloseHandle(hReadFile);
			}
			break;
		/*-----------------------------------*/
		case ID_DISPLAY:
		{
			ListView_DeleteAllItems(hwndListView);
			hReadFile = CreateFile(".\\Data.txt",GENERIC_READ, 0, NULL, OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL,NULL);
			if(hReadFile == INVALID_HANDLE_VALUE)
			{
				MessageBox(hwnd,TEXT("CreateFIle Read Fail"),TEXT("Message"),MB_OK);
			}
			//pISubtract->SubtractionOfTwoIntegers(hReadFile,DataBuffer,&dwBytesRead);
			//wsprintf(str,"%s= %d",DataBuffer,dwBytesRead);
			//MessageBox(hwnd,str,TEXT("Message"),MB_OK);
			//Read File Operation
			index = 0;
			TCHAR STR1[255] = {};
			//SUPER Read >>>>>>>>>>>>>>>>
			while( MyReadFile(hReadFile,DataBuffer,&dwBytesRead) && dwBytesRead > 0)
			{
			
				wsprintf(str,TEXT("%s"),DataBuffer);
				n = 0;
				i = 0;
				space = 0;
				size = 0;
				flag = 0;
				//MessageBox(hwnd,str,TEXT("Message"),MB_OK);
				memset(&ot, 0, sizeof(ot));
				memset(&salary,0,sizeof(salary));
				memset(&age,0,sizeof(salary));
				
				while(n <= sizeof(str))
				{
					if(space == 0)
					{	//Name
						if(str[n] != '!')
						{
							ot.name[i] = str[n];
							size = size + 1;
							i = i + 1;
						}
						else 
						{
							i = 0;
							space = 1;
							n = n + 1;
						}
					}
					//Address
					if(space == 1)
					{
						if(str[n] != '!')
						{
							ot.address[i] = str[n];
							i = i + 1;
						}
						else
						{
							i = 0;
							space = 2;
							n = n + 1;
						}
					}
					//Age
					if(space == 2)
					{
						if(str[n] != '!')
						{
							age[i] = str[n];
							i = i + 1;
						}
						else
						{
							i = 0;
							space = 3;
							n = n + 1;
						}
					}
					//Salary
					if(space == 3)
					{
						if(str[n] != '!')
						{
							salary[i] = str[n];
							i = i + 1;
						}
						else
						{
							i = 0;
							space = 4;	
							n = n + 1;
						}
					}	
					//Marrage Status
					if(space == 4)
					{
						if(str[n] != '!')
						{
							status[i] = str[n];
							i = i + 1;
						}
						else
						{
							break;
						}
					}
					n = n + 1;
				}
				GetDlgItemText(hDlg,ID_ETNAME,entername,50);
				wsprintf(str,TEXT("%s"),ot.name);

				/*for( loop1 = 0; loop1 < size; loop1++)
				{
					if(ot.name[loop1+1] == entername[loop1])
						flag = flag + 1;
					//wsprintf(str,TEXT("%c %c %d"),ot.name[loop1+1],entername[loop1], loop1);
					//MessageBox(hwnd,str,TEXT("MESSAGE"),MB_OK);
				}
				//wsprintf(str,TEXT("flag:-%d size:-%d"),flag,size);
				//MessageBox(hwnd,str,TEXT("MESSAGE"),MB_OK);
				if(flag !=size)
				{	flag = 0;
					continue;
				}
				flag = 0;*/
				memset(&lvI, 1, sizeof(LVITEM));////// khup khup khup khup mahatvacha aahe he..............!!!!!!!!!!!!!!!
				//SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
				lvI.mask = LVIF_TEXT;// | LVIF_COLFMT | LVIF_COLUMNS;
			
				//lvI.pszText = (LPSTR)"NAME";
				//lvI.iItem = 0;
				//lvI.stateMask = 0;
				//lvI.state = 0;
				lvI.iSubItem = 0;
			
	
				lvI.iItem = index;
				for(int SubItem = 0; SubItem <5;SubItem++)
				{	
					lvI.iSubItem = SubItem;
					switch(lvI.iSubItem)
					{
					case 0:
						lvI.pszText = (LPSTR)ot.name;
						ListView_InsertItem(hwndListView, &lvI);
						break;
					case 1:
						lvI.pszText = (LPSTR)ot.address;
						SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						break;
					case 2:
						lvI.pszText = (LPSTR)age;
						SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						break;
					case 3:
						lvI.pszText = (LPSTR)salary;
						SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						break;
					case 4:
						lvI.pszText = (LPSTR)status;
						SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
						break;
					}
					//SendMessage(hwndListView, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvI);
				} 
			
			index = index + 1;	
			//MessageBox(hwnd, age,TEXT("Message1"),MB_OK);
			
			}
			//End of ReadOperation
			CloseHandle(hReadFile);	
		}
		break;
		/*___________________________________*/
		}//case end
		return(TRUE);
	}	
	return(FALSE);
}

BOOL MyReadFile(HANDLE hReadFile,char *DataBuffer, DWORD *dwBytesRead)
{
	BOOL Number;
	pIRead->NiceRead(hReadFile,DataBuffer,dwBytesRead,&Number);
	return(Number);
}

BOOL ZeroStrCmp(char *str)
{
	int count = 0;
	for(int i = 0 ; i < sizeof(str);i++)
	{
		if(in.name[i] == 0)
		{
			count = count + 1;		
		}
	}
	if(count == sizeof(sizeof(str)))
	{ 
		return(-1);
	}
	else
	{
		return(0);
	}	 
}
