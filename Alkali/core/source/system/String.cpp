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


		tString cString::SubString(const tString& asString, int alStart, int alCount)
		{
			size_t lStringSize = asString.length();
			if (alStart >= lStringSize) return "";
			if (alStart + alCount > lStringSize) alCount = lStringSize - alStart;

			if (alCount == 0) return asString.substr(alStart);
			else return asString.substr(alStart, alCount);
		}

		twString cString::SubStringW(const twString& asString, int alStart, int alCount)
		{
			size_t lStringSize = asString.length();
			if (alStart >= lStringSize) return L"";
			if (alStart + alCount > lStringSize) alCount = lStringSize - alStart;

			if (alCount == 0) return asString.substr(alStart);
			else return asString.substr(alStart, alCount);
		}




		tString cString::Replace(const tString& asString, const tString& asFind, const tString& asReplace)
		{
			tString sTemp = asString;

			for (size_t i = 0; i < asString.size(); i++)
			{
				if (asString[i] == asFind[0])
					sTemp[i] = asReplace[0];
			}

			return sTemp;
		}

		twString cString::ReplaceW(const twString& asString, const twString& asFind, const twString& asReplace)
		{
			twString sTemp = asString;

			for (size_t i = 0; i < asString.size(); i++)
			{
				if (asString[i] == asFind[0])
					sTemp[i] = asReplace[0];
			}
			return sTemp;
		}



		int cString::FindFirstOfChar(const tString& asString, const tString& acChar)
		{
			int pos = 1;
			for (size_t i = 0; i < asString.size(); i++)
			{
				if (asString.substr(i, acChar.size()) == acChar) {
					pos = (int)i;
					break;
				}
			}
			return pos;
		}

		int cString::FindFirstOfCharW(const twString& asString, const twString& acChar)
		{
			int pos = 1;
			for (size_t i = 0; i < asString.size(); i++)
			{
				if (asString.substr(i, acChar.size()) == acChar) {
					pos = (int)i;
					break;
				}
			}
			return pos;
		}



		int cString::FindLastOfChar(const tString& asString, const tString& acChar)
		{
			int pos = 1;
			for (size_t i = 0; i < asString.size(); i++)
			{
				if (asString.substr(i, acChar.size()) == acChar) {
					pos = (int)i;
				}
			}
			return pos;
		}

		int cString::FindLastOfCharW(const twString& asString, const twString& acChar)
		{
			int pos = 1;
			for (size_t i = 0; i < asString.size(); i++)
			{
				if (asString.substr(i, acChar.size()) == acChar) {
					pos = (int)i;
				}
			}
			return pos;
		}



		tString cString::FileExtension(const tString& asFileName)
		{
			return "";
		}

		twString cString::FileExtensionW(const twString& asFileName)
		{
			twString sName = FileNameW(asFileName);
			int lPos = FindLastOfCharW(asFileName, L".");
			if (lPos < 0) return L"";
			return asFileName.substr(lPos + 1);
		}

		tString cString::FileName(const tString& asFileName)
		{
			int lPos1 = FindLastOfChar(asFileName, "/");
			int lPos2 = FindLastOfChar(asFileName, "\\");
			int lPos = lPos1 > lPos2 ? lPos1 : lPos2;
			if (lPos < 0) return asFileName;
			else
			return asFileName.substr(lPos+1);
		}

		twString cString::FileNameW(const twString& asFileName)
		{
			int lPos1 = FindLastOfCharW(asFileName, L"/");
			int lPos2 = FindLastOfCharW(asFileName, L"\\");
			int lPos = lPos1 > lPos2 ? lPos1 : lPos2;
			if (lPos < 0) return asFileName;
			else
				return asFileName.substr(lPos + 1);
		}




}