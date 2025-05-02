#include <stdio.h>
#include <string>

#ifndef ALK_SYSTYPES_H
#define ALK_SYSTYPES_H
//#pragma warning ( disable : 4996)

namespace alkali
{

	enum ePlatform
	{
		ePlatform_Windows,

		ePlatform_LastEnum
	};

	enum eSystemPath
	{
		eSystemPath_Personal,

		eSystemPath_LastEnum
	};

	typedef std::string tString;
	typedef std::wstring tWString;

#endif
}