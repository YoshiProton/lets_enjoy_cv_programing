#include "stdafx.h"
#include "Utility.h"

CUtility::CUtility()
{
}


CUtility::~CUtility()
{
}

BYTE CUtility::GetR(COLORREF rgb)
{
	return (LOBYTE((rgb) >> 16));
}

BYTE CUtility::GetG(COLORREF rgb)
{
	return (LOBYTE((rgb) >> 8));
}

BYTE CUtility::GetB(COLORREF rgb)
{
	return (LOBYTE(rgb));
}

///<summary>
///Ž©ì‚ÌRGB<-->HSV•ÏŠ·ŠÖ”
///</summary>
void CUtility::ConvertRGBtoHSV(int r, int g, int b, int* pHue, int* pSaturation, int* pBrightness)
{
	int max = 0;
	int min = 255;

	if (r >= max) max = r;
	if (g >= max) max = g;
	if (b >= max) max = b;

	if (r <= min) min = r;
	if (g <= min) min = g;
	if (b <= min) min = b;

	int v = max;
	int s = (int)(255.0 * (max - min) / max);
	int h = 0;

	if (r == g == b || max == min)
		h = 0;
	else if (r == max)
		h = 60 * (g - b) / (max - min);
	else if (g == max)
		h = 60 * ((b - r) / (max - min)) + 120;
	else if (b == max)
		h = 60 * ((r - g) / (max - min)) + 240;

	if (h < 0)
		h += 360;

	h /= 2;

	*pHue = h;
	*pSaturation = s;
	*pBrightness = v;
}

///<summary>
///Ž©ì‚ÌHSV<-->RGB•ÏŠ·ŠÖ”i•s‹ï‡‚ ‚èj
///</summary>
void CUtility::ConvertHSVtoRGB(int h, int s, int v, int* r, int* g, int* b)
{
	int max = v;
	int min = max - (max * s / 255);
	
	double hh = h * 2.0;

	if (hh >= 0 && hh < 60)
	{
		*r = max;
		*g = (int)((hh / 60) * (max - min) + min);
		*b = min;
	}
	else if (hh >= 60 && hh < 120)
	{
		*r = (int)(((120 - hh) / 60) * (max - min) + min);
		*g = max;
		*b = min;
	}
	else if (hh >= 120 && hh < 180)
	{
		*r = min;
		*g = max;
		*b = (int)(((hh - 120) / 60) * (max - min) + min);
	}
	else if (hh >= 180 && hh < 240)
	{
		*r = min;
		*g = (int)(((240 - hh) / 60) * (max - min) + min);
		*b = max;
	}
	else if (hh >= 240 && hh < 300)
	{
		*r = (int)(((hh - 240) / 60) * (max - min) + min);
		*g = min;
		*b = max;
	}
	else if (hh >= 300 && hh < 360)
	{
		*r = max;
		*g = min;
		*b = (int)(((360 - hh) / 60) * (max - min) + min);
	}
}