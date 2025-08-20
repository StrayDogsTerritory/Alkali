#ifndef ALK_STRING_H
#define ALK_STRING_H

#include <string>
#include <vector>
#include <list>

namespace alk {


	typedef std::string tString;
	typedef std::wstring twString;
	typedef std::list<tString> tStringList;

	typedef std::vector<tString> tStringVector;
	typedef std::vector<twString> twStringVector;
	typedef std::list<twString> twStringList;

	class cString
	{
	public:
		/////////////////
		// STRING CONVERSION FUNCTIONS

		static twString ToWideChar(const tString& asString);
		static tString To8BitChar(const twString& asString);

		/////////////////////
		// STRING MODIFICATION AND SEARCHING

		static tString ToLowerCase(const tString& asString);
		static twString ToLowerCaseW(const twString& asString);

		static tString ToUpperCase(const tString& asString);
		static twString ToUpperCaseW(const twString& asString);

		static tString SubString(const tString& asString, int alStart, int alCount = 0);
		static twString SubStringW(const twString& asString, int alStart, int alCount = 0);

		static tString Replace(const tString& asString, const tString& asFind, const tString& asReplace);
		static twString ReplaceW(const twString& asString, const twString& asFind, const twString& asReplace);
		
		static int FindFirstOfChar(const tString& asString, const tString& acChar);
		static int FindFirstOfCharW(const twString& asString, const twString& acChar);

		static int FindLastOfChar(const tString& asString, const tString& acChar);
		static int FindLastOfCharW(const twString& asString, const twString& acChar);
		
		///////////////////
		// FILE AND DIR FUNCTIONS

		static tString FileExtension(const tString& asFileName);
		static twString FileExtensionW(const twString& asFileName);
		
		static tString FileName(const tString& asFileName);
		static twString FileNameW(const twString& asFileName);
	};

}
#endif