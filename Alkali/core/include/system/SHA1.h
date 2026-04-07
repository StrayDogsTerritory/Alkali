#ifndef ALK_SHA1_H
#define ALK_SHA1_H

#include "system/SystemTypes.h"
#include <string>
namespace alk {

	class cSHA1
	{
	public:
		cSHA1();
		~cSHA1();

		void Reset();

		tString Hash(const tString& asString);
		twString Hash(const twString& asString);
		

	private:

		void Input(const unsigned char* asData, unsigned int alLength);

		void PadMessage();
		void ProcessMessage();

		char* Format() const;

		unsigned int mlMessageBlockIndex;
		unsigned char mlMessageBlock[64];
		unsigned int H[5]; // initial hashing values
		bool mbComputed;
	};
}

#endif
