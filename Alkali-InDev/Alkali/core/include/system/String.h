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
		// STRING MODIFICATION


		///////////////////
		// FILE AND DIR FUNCTIONS

	private:
		
	};

}
#endif