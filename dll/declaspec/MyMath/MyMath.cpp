// MyMath.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
//Header file
#include <windows.h>

//DLL main 
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReson, LPVOID lpReserved)
{
	switch (dwReson)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return (TRUE);
}

extern "C" __declspec(dllexport) int MakeSquare(int num)
{
	return (num*num);
}

extern "C" BOOL IsNumberNegative(int num)
{
	if (num < 0)
	{
		return (TRUE);
	}
	else
	{
		return FALSE;
	}
}







