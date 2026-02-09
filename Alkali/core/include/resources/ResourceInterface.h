#ifndef ALK_RESOURCEINTERFACE_H
#define ALK_RESOURCEINTERFACE_H

//#include "resources/ResourceLoader.h"

namespace alk {

	class iResourceLoader;

	class iResourceInterface
	{
		iResourceInterface() {}
		virtual ~iResourceInterface() {}

		virtual void SetupBitmapLoader(iResourceLoader* apResourceLoader)=0;
		virtual bool Init() = 0;
	};

}

#endif
