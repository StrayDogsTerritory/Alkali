#ifndef ALK_STRING_H
#define ALK_STRING_H

#include <string>


namespace alk {


	typedef std::string tString;
	typedef std::wstring twString;

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

		static tString SubString(const tString& asString, const tString& asSubString);
		static twString SubString(const twString& asString, const tString& asSubString);


		///////////////////
		// FILE AND DIR FUNCTIONS

		tString FileExtension(const tString& asFileName);
		twString FileExtensionW(const twString& asFileName);

	private:
		
	};

}
#endif