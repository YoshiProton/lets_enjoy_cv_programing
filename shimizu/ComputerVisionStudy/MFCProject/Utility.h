#pragma once
class CUtility
{
public:
	CUtility();
	~CUtility();

	static void ConvertRGBtoHSV(int, int, int, int*, int*, int*);
	static void ConvertHSVtoRGB(int, int, int, int*, int*, int*);

	static BYTE GetR(COLORREF);
	static BYTE GetG(COLORREF);
	static BYTE GetB(COLORREF);
};

