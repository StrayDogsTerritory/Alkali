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

		tString cString::To8BitChar(const twString& asString)
		{
			tString sTemp;
			sTemp.resize(asString.size());

			for (size_t i = 0; i < asString.length(); ++i)
			{
				if (asString[i] > 255)
					sTemp[i] = '?'; 
				else
					sTemp[i] = (unsigned char)asString[i];
			}

			return sTemp;
		}

		tString cString::ToLowerCase(const tString& asString)
		{
			tString sTemp;
			sTemp.resize(asString.size());	

			for (size_t i = 0; i < asString.size(); i++)
			{
				sTemp[i] = tolower(asString[i]);
			}

			return sTemp;

		}

		twString cString::ToLowerCaseW(const twString& asString)
		{
			twString sTemp;
			sTemp.resize(asString.size());
			for (size_t i = 0; i < asString.size(); i++)
			{
				sTemp[i] = tolower(asString[i]);
			}

			return sTemp;
		}

		tString cString::ToUpperCase(const tString& asString)
		{
			tString sTemp;
			sTemp.resize(asString.size());
			for (size_t i = 0; i < asString.size(); ++i)
			{
				sTemp[i] = toupper(asString[i]);
			}
			return sTemp;
		}

		twString cString::ToUpperCaseW(const twString& asString)
		{
			twString sTemp;
			sTemp.resize(asString.size());
			for (size_t i = 0; i < asString.size(); ++i)
			{
				sTemp[i] = toupper(asString[i]);
			}
			return sTemp;
		}


}