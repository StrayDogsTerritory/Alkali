#include "system/String.h"
#include <string>

// maybe these should be temporary until I'm done testing the hash function;
#include "system/Platform.h"
#include "engine/LogWriter.h"

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

		tString cString::toString(const char* asString, const tString& asFallback)
		{
			if (asString == NULL) return asFallback;
				return asString;
		}

		int cString::ToInt(const char* asString, int alFallback)
		{
			if (asString == NULL) return alFallback;
			return atoi(asString);
		}

		float cString::ToFloat(const char* asString, float afFallback)
		{
			if (asString == NULL) return afFallback;
			return atof(asString);
		}

		bool cString::ToBool(const char* asString, bool abFallback)
		{
			if (asString == NULL) return abFallback;
			tString sTemp = ToLowerCase(asString);
			return sTemp == "true" ? true : false;
		}

		unsigned int cString::Hash(const tString& asString)
		{
			unsigned long long lInitTime = cPlatform::GetAppTime();
			unsigned int lHash;

			// using the SHA-1 hash values
			lHash = 0x67452301;

			
			size_t lLength = asString.length();
			const char* sData = asString.c_str();
			unsigned int lMagicNumber[5];
			lMagicNumber[0] = 0x67452301;
			lMagicNumber[1] = 0xefcfab89;
			lMagicNumber[2] = 0x98badcfe;
			lMagicNumber[3] = 0x10325476;
			lMagicNumber[4] = 0xc3d2e1f0;

			for (int i = 0; i<lLength; i++)
			{
				lHash = lHash ^ sData[i];
				lHash *= lMagicNumber[i];
			}

			int lTime = cPlatform::GetAppTime() - lInitTime;

			//Log("hasing %s took %d secs\n", asString.c_str(), lTime);

			return lHash;
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
			int pos = -1;
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
			int pos = -1;
			for (size_t i = 0; i < asString.size(); i++)
			{
				if (asString.substr(i, acChar.size()) == acChar) {
					pos = (int)i;
				}
			}
			return pos;
		}

		tString cString::GetLastChar(const tString& asString)
		{
			if (asString == "") return "";
			else
			return asString.substr(asString.length()-1);
		}

		twString cString::GetLastCharW(const twString& asString)
		{
			if (asString == L"") return L"";
			if (asString.length() == 0) return L"";
			
			return asString.substr(asString.length() - 1);
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
			if (FindLastOfChar(asFileName, ".") < 0) { return asFileName; }
			int lPos1 = FindLastOfChar(asFileName, "/");
			int lPos2 = FindLastOfChar(asFileName, "\\");
			int lPos = lPos1 > lPos2 ? lPos1 : lPos2;

			if (lPos <= 0) 
				return asFileName;
			else
				return asFileName.substr(lPos+1);
		}

		twString cString::FileNameW(const twString& asFileName)
		{
			int pos1 = FindLastOfCharW(asFileName, L"\\");
			int pos2 = FindLastOfCharW(asFileName, L"/");
			int pos = pos1 > pos2 ? pos1 : pos2;

			if (pos <= 0)
				return asFileName;
			else
				return asFileName.substr(pos + 1);
		}

		tString cString::SetFilePath(const tString& asFileName, const tString& asNewPath)
		{
			tString sSepp = "";
			if (GetLastChar(asNewPath) != "/" && GetLastChar(asNewPath) != "\\")
				sSepp = "/";
			return asNewPath + sSepp + FileName(asFileName);
		}

		twString cString::SetFilePathW(const twString& asFileName, const twString& asNewPath)
		{
			twString sSepp = L"";
			if (GetLastCharW(asNewPath) != L"/" && GetLastCharW(asNewPath) != L"\\")
				sSepp = L"/";

			return asNewPath + sSepp + FileNameW(asFileName);
		}



}