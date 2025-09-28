#ifndef ALK_SHA1_H
#define ALK_SHA1_H

#include "system/String.h"

namespace alk {

	class cSHA1
	{
	public:
		cSHA1();
		~cSHA1();

		void Reset();

		tString ProcessMessage(const tString& asHash);

	private:
		unsigned int* H[5];
	};

}

#endif
