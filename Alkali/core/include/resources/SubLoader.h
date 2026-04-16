#ifndef ALK_SUBLOADER_H
#define ALK_SUBLOADER_H

#include "system/String.h"

#include <list>
#include <vector>

/*
* Created by Simon Stroomer
* File extension specific loaders, therefore sub-loader hehe :)
*/

namespace alk {

	typedef std::list<tString> tLstExtensions;
	typedef tLstExtensions::iterator tExtensionIt;

	class iSubLoader
	{
	public:

		//-------------------------------------------------------------------------------------

		iSubLoader() {} //constructor
		virtual ~iSubLoader() {} //destructor

		//-------------------------------------------------------------------------------------

		bool IsSupported(const tString& asExtension); //check if a specific extension is supported
		void AddExtension(const tString& asExtension); //make the specific extension supported in the sub loader

		//-------------------------------------------------------------------------------------

		tLstExtensions mLstExtensions;

	protected:
		
	};

}
#endif 
