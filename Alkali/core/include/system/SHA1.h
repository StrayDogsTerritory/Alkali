#ifndef ALK_SHA1_H
#define ALK_SHA1_H

#include "system/SystemTypes.h"
#include <string>

/*
* Created by Simon Stroomer
* hashes a std::string or a std::wstring into a 180 bit string as specified by FIPS 180-4 found here: http://dx.doi.org/10.6028/NIST.FIPS.180-4
*/

namespace alk {

	class cSHA1
	{
	public:

		//----------------------------------------------------------

		cSHA1(); // constructor
		~cSHA1(); // destructor

		//----------------------------------------------------------
		
		void Reset(); // reset values to default. Should be run after each hash

		//----------------------------------------------------------

		tString Hash(const tString& asString); // hashes input std::string into 160 bit message digest
		twString Hash(const twString& asString); // hashes input std::wstring into 160 bit message digest

		//----------------------------------------------------------
	private:

		//----------------------------------------------------------

		void Input(const unsigned char* asData, unsigned int alLength); // read message into the message block

		//----------------------------------------------------------

		void PadMessage(); // pad the message into some multiple of 512 bits

		//----------------------------------------------------------

		void ProcessMessage(); // hashes the message

		//----------------------------------------------------------

		tString Format() const; // adds the hashes together to formulate the final string

		//----------------------------------------------------------

		unsigned int mlLength; // length of message, to be added at the end of the padded message

		//----------------------------------------------------------
		
		unsigned int ROTL(unsigned int W, unsigned int N); // circularly shifts bits

		//----------------------------------------------------------
		
		unsigned int mlMessageBlockIndex; //position of the message iterator

		//----------------------------------------------------------

		unsigned char mlMessageBlock[64]; // 512 bit message block

		//----------------------------------------------------------

		unsigned int H[5]; // hash values

		//---------------------------------------------------------
	};
}

#endif
