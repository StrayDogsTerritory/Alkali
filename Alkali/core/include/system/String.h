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

		twString ToWideChar(const tString& asString);

		/////////////////////
		// STRING MODIFICATION AND SEARCHING

		tString ToLowerCase(const tString& asString);
		twString ToLowerCaseW(const twString& asString);

		tString ToUpperCase(const tString& asString);
		twString ToUpperCaseW(const twString& asString);

		tString SubString(const tString& asString, const tString& asSubString);
		twString SubString(const twString& asString, const tString& asSubString);


		///////////////////
		// FILE AND DIR FUNCTIONS

		tString FileExtension(const tString& asFileName);
		twString FileExtensionW(const twString& asFileName);

	private:
		
	};

}
#endif