#pragma once 

class ISum :public IUnknown
{
	public:
		virtual HRESULT __stdcall SumOfTwoIntegers(int ,int ,int *) = 0;
};

class ISubtract :public IUnknown
{
	public:
		virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};

/*
// {EC21A0DA-EDC5-4922-B92A-E8F27ACD357A}
IMPLEMENT_OLECREATE(<<class>>, <<external_name>>, 
0xec21a0da, 0xedc5, 0x4922, 0xb9, 0x2a, 0xe8, 0xf2, 0x7a, 0xcd, 0x35, 0x7a);
*/
const CLSID CLSID_SumSubtract =
{0xec21a0da, 0xedc5, 0x4922, 0xb9, 0x2a, 0xe8, 0xf2, 0x7a, 0xcd, 0x35, 0x7a};


/*
// {B1836C61-E12C-48B9-A550-2BEFE967F7F2}
IMPLEMENT_OLECREATE(<<class>>, <<external_name>>, 
0xb1836c61, 0xe12c, 0x48b9, 0xa5, 0x50, 0x2b, 0xef, 0xe9, 0x67, 0xf7, 0xf2);
*/
const IID IID_ISum = {0xb1836c61, 0xe12c, 0x48b9, 0xa5, 0x50, 0x2b, 0xef, 0xe9, 0x67, 0xf7, 0xf2};

/*
// {FC548F0D-D3CC-46EF-9F76-CFE150A4B1B1}
IMPLEMENT_OLECREATE(<<class>>, <<external_name>>, 
0xfc548f0d, 0xd3cc, 0x46ef, 0x9f, 0x76, 0xcf, 0xe1, 0x50, 0xa4, 0xb1, 0xb1);
*/
const IID IID_ISubtract = {0xfc548f0d, 0xd3cc, 0x46ef, 0x9f, 0x76, 0xcf, 0xe1, 0x50, 0xa4, 0xb1, 0xb1};

