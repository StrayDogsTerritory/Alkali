#ifndef ALK_RESOURCESSDL_H
#define ALK_RESOURCESSDL_H

#include "resources/ResourceInterface.h"

namespace alk {

	class cResourcesSDL : public iResourceInterface
	{
		cResourcesSDL();
		~cResourcesSDL();

		void SetupBitmapLoader(iResourceLoader* apResourceLoader);
	};

}

#endif