#ifndef ALK_SHA1_H
#define ALK_SHA1_H

#include "system/SystemTypes.h"

namespace alk {

	class cSHA1
	{
	public:
		cSHA1();
		~cSHA1();



	private:
		unsigned int H[5]; // initial hashing values
	};

}

#endif
