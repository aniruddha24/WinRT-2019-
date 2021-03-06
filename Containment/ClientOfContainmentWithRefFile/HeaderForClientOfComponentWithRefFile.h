#pragma once
class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};
class ISubtract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};

class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;
};

class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0;
};
/*// {51667B37-5C18-4F3C-A852-00625C1E6DF0}*/
const CLSID CLSID_SumSubtract = { 0x51667b37, 0x5c18, 0x4f3c, 0xa8, 0x52, 0x0, 0x62, 0x5c, 0x1e, 0x6d, 0xf0 };


const IID IID_ISum = { 0x9a76f8f0, 0x2ba4, 0x48a3, 0xa2, 0xbf, 0x2b, 0xde, 0x70, 0xff, 0x2a, 0xf6 };


const IID IID_ISubtract = { 0x942b0fca, 0xcf06, 0x496f, 0x9a, 0x24, 0xa7, 0x69, 0xd5, 0x63, 0x83, 0x3e };


const IID IID_IMultiplication = { 0x556eb284, 0x6087, 0x4122, 0xaa, 0x2e, 0xf7, 0xd1, 0x5b, 0x51, 0x9d, 0xb3 };


const IID IID_IDivision = { 0x285c2a78, 0x86d4, 0x410c, 0xa6, 0xbd, 0xf7, 0xcd, 0xd4, 0x5d, 0xa7, 0x58 };


