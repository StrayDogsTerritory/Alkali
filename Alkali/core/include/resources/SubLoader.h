#ifndef ALK_SUBLOADER_H
#define ALK_SUBLOADER_H

#include "system/String.h"

#include <list>
#include <vector>

namespace alk {

	typedef std::list<tString> tLstExtensions;
	typedef tLstExtensions::iterator tExtensionIt;

	class iSubLoader
	{
	public:
		iSubLoader() {}
		virtual ~iSubLoader() {}

		bool IsSupported(const tString& asExtension);
		void AddExtension(const tString& asExtension);

		tLstExtensions mLstExtensions;
	protected:
		
	};

}
#endif 
