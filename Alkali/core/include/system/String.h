#ifndef ALK_STRING_H
#define ALK_STRING_H

#include "system/SystemTypes.h"
#include <string>
#include <vector>
#include <list>

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace alk {

	// putting char arrays here even though it's only really being used for word related things.
	typedef std::vector<char> tByteVec;
	typedef std::vector<char*> t8ByteVec;



	typedef std::list<tString> tStringList;

	typedef std::vector<tString> tStringVector;
	typedef std::vector<tString>::iterator tStringVectorIt;
	typedef std::vector<twString> twStringVector;
	typedef std::vector<twString>::iterator twStringVectorIt;

	typedef std::list<tString> tStringList;
	typedef std::list<tString>::iterator tStringListIt;
	typedef std::list<twString> twStringList;
	typedef std::list<twString>::iterator twStringListIt;

	

	class cString
	{
	public:
		/////////////////
		// STRING CONVERSION FUNCTIONS

		static twString ToWideChar(const tString& asString);
		static tString To8BitChar(const twString& asString);

		static tString toString(const char* asString, const tString& asFallback = "");
		static int ToInt(const char* asString, int alFallback = 0);
		static float ToFloat(const char* asString, float afFallback = 0.0f);
		static bool ToBool(const char* asString, bool abFallback = false);
		static tVector2l ToVector2l(const char* asString, tVector2l avFallback = 0);
		static tVector2f ToVector2f(const char* asString, tVector2f avFallback = 0);
		static tVector3l ToVector3l(const char* asString, tVector3l avFallback = 0);
		static tVector3f ToVector3f(const char* asString, tVector3f avFallback = 0);
		

		static unsigned int Hash(const tString& asString);

		static tString ToStringInt(int alX, const tString &asFallback="");
		static tString ToStringFloat(float afX, const tString& asFallback="");
		static tString ToStringBool(bool abX, const tString& asFallback="");
		static tString ToStringVector2l(tVector2l avVec, const tString& asFallback = "");
		static tString ToStringVector2f(tVector2f avVec, const tString& asFallback = "");
		static tString ToStringVector3l(tVector3l avVec, const tString& asFallback = "");
		static tString ToStringVector3f(tVector3f avVec, const tString& asFallback = "");
		/////////////////////
		// STRING MODIFICATION AND SEARCHING

		static tStringVector& GetVecFromString(const tString& asString, tStringVector& avVec);
		static twStringVector& GetVecFromStringW(const twString& asString, twStringVector& avVec);

		static tIntVector GetVecFromInt(const tString& asString, tIntVector& avVec);
		static tFloatVector GetVecFromFloat(const tString& asString, tFloatVector& avVec);

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
		
		static tString GetLastChar(const tString& asString);
		static twString GetLastCharW(const twString& asString);
		///////////////////
		// FILE AND DIR FUNCTIONS

		static tString FileExtension(const tString& asFileName);
		static twString FileExtensionW(const twString& asFileName);
		
		static tString FileName(const tString& asFileName);
		static twString FileNameW(const twString& asFileName);

		static tString GetFilePath(const tString& asFileName);
		static twString GetFilePathW(const twString& asFileName);

		static tString SetFilePath(const tString& asFileName, const tString& asNewPath);
		static twString SetFilePathW(const twString& asFileName, const twString& asPath);

		static tString AddSlashAtEnd(const tString& asString, char asSlash = '/');
		static twString AddSlashAtEndW(const twString& asString, wchar_t asSlash = L'/');
	};

}
#endif