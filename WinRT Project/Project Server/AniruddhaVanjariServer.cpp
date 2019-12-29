#include <windows.h>
#include "AniruddhaVanjariServer.h"


//class declarations
class CWriteRead :public IWrite,IRead
{
private:
	long m_cRef;
public:
	//constructor method declaration
	CWriteRead(void);
	//destructor method declaration
	~CWriteRead(void);

	//IUnknown specific method declaration (INHERITED)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IWrite specific method declarations (inhertied) (HANDLE hFile, LPCVOID DataBuffer,LPDWORD *datawritten)
	HRESULT __stdcall NiceWrite(HANDLE,char *, DWORD *);

	//ISubtract specific method declarations (inherited)
	HRESULT __stdcall NiceRead(HANDLE, char *, DWORD *,int *);
};

class CWriteReadClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method declaration
	CWriteReadClassFactory(void);

	//destructor method declaration
	~CWriteReadClassFactory(void);

	//IUnknown specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declaration (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberofActiveComponents = 0; //Number of active components
long glNumberofServerLocks = 0;	//Number of lock in this dll

//DllMain
BOOL WINAPI DllMAin(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	char str1[255];
	wsprintf(str1, TEXT("DLL MESSAGE"));
	MessageBox(NULL, str1, TEXT(" DLL Message"), MB_OK);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

//Implementation of CSumSubract's Constructor Method
CWriteRead::CWriteRead(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberofActiveComponents);
}

//Implementation of CSumSubract's Destructor Method
CWriteRead::~CWriteRead(void)
{
	InterlockedDecrement(&glNumberofActiveComponents);

}

//Implementation of CWriteRead's IUnknown's Methods
HRESULT CWriteRead::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IWrite *>(this);
	else if (riid == IID_IWrite)
		*ppv = static_cast<IWrite *>(this);
	else if (riid == IID_IRead)
		*ppv = static_cast<IRead *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();

	return(S_OK);
}

ULONG CWriteRead::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CWriteRead::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of IWrite's Methods
HRESULT CWriteRead::NiceWrite(HANDLE hFile, char *DataBuffer,DWORD *datawritten)
{
	WriteFile(hFile, DataBuffer,100,datawritten,NULL);
	return(S_OK);
}

//Implentation of IRead's Methods
HRESULT CWriteRead::NiceRead(HANDLE hReadFile, char *DataBuffer,DWORD *dwBytesRead, int *Number)
{
	*Number =  ReadFile(hReadFile,DataBuffer,100,dwBytesRead, NULL);
	return(S_OK);
}

//Implementation of CWriteReadClassFactory's Constructor Method
CWriteReadClassFactory::CWriteReadClassFactory(void)
{
	m_cRef = 1;
}

//Implementation of CWriteReadClassFactory's Constructor Method
CWriteReadClassFactory::~CWriteReadClassFactory(void)
{
	
}

//Implementation of CWriteReadClassFactory's IClassFactory's Methods
HRESULT CWriteReadClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CWriteReadClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return(m_cRef);
}

ULONG CWriteReadClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
//Implementation of CWriteReadClassFactory's ClassFaxtory's Methods
HRESULT CWriteReadClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CWriteRead *pCWriteRead = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	pCWriteRead = new CWriteRead;

	if (pCWriteRead == NULL)
		return (E_OUTOFMEMORY);
	hr = pCWriteRead->QueryInterface(riid, ppv);

	pCWriteRead->Release();
	return(hr);
}

HRESULT CWriteReadClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberofServerLocks);
	else
		InterlockedDecrement(&glNumberofServerLocks);
	return(S_OK);
}

//Implemenetion of Export Function From This DLL
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CWriteReadClassFactory *pCWriteReadClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_CWriteRead)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCWriteReadClassFactory = new CWriteReadClassFactory;
	if (pCWriteReadClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCWriteReadClassFactory->QueryInterface(riid, ppv);
	pCWriteReadClassFactory->Release();

	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberofActiveComponents == 0) && (glNumberofServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}


