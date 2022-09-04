#pragma once
#include "Common.h"

class CToolBox
{
	GENERATED_ONLY_STATIC(CToolBox)

public:
	static const string ToNumberWithComma(const int InNumber) {
		string numberString(to_string(InNumber));
		regex pattern("\\B(?=(\\d{3})+(?!\\d))");

		return std::regex_replace(numberString, pattern, ",");
	}
	static const char* UTF8ToANSI(const char* pszCode)
	{
		BSTR bstrWide;
		char* pszAnsi;
		int nLength;

		nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, NULL, NULL);
		bstrWide = SysAllocStringLen(NULL, nLength);

		MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

		nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
		pszAnsi = new char[nLength];

		WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
		SysFreeString(bstrWide);

		return pszAnsi;
	}
};

