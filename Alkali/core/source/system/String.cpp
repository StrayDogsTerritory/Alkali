#include "system/String.h"
#include <string>
namespace alk {
	

		twString cString::ToWideChar(const tString& asString)
		{
			twString sTemp;

			size_t size = mbstowcs(NULL, &asString[0],0);
			sTemp.resize(size);

			mbstowcs(&sTemp[0], &asString[0], size);

			return sTemp;
		}


}