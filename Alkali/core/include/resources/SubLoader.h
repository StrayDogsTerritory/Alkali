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

		bool IsSupported(const twString& asExtension);
		void AddExtension(const twString& asExtension);

	private:
		tLstExtensions mLstExtensions;
	};

}
#endif 
