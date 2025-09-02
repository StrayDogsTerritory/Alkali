#include "system/Platform.h"

#include "SDL3/SDL.h"

#include <cstdarg>

namespace alk{

	void cPlatform::Sleep(int alMS)
	{
		SDL_Delay(alMS);
	}
	
	//--------------------------------------

	unsigned long long cPlatform::GetAppTime()
	{
		return SDL_GetTicks();
	}

	//--------------------------------------
	void cPlatform::CreateMessageBox(eMessageBoxType aeMessageBoxType, const wchar_t* asCaption, const wchar_t* fmt, ...)
	{
		va_list List;
		va_start(List, fmt);
		twStringList lst;
		//FindFilesInDirectory(lst, L"test/test", L"*.*", false);
		 CreateMessageBoxPlatform(aeMessageBoxType, asCaption, fmt, List);
		va_end(List);

		
	}
}