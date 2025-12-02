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

		void input();

		void Result();

		unsigned int PadMessage();

		unsigned int ProcessMessage();

		//functions
		unsigned int ROTL(int N, unsigned int W);
		unsigned int ROTR(int N, unsigned int W);

	private:
		unsigned int H[5]; // initial hashing values
	};

}

#endif
