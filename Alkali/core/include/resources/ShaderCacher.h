#ifndef ALK_SHADERCACHER_H
#define ALK_SHADERCACHER_H

#include "system/SystemTypes.h"

namespace alk {

	class cXmlDocument;

	class cShaderCache // should this derive from a base cache class?
	{
	public:
		cShaderCache(const char* asShaderBinary);


		bool Cache();

	private:
	};

}

#endif
