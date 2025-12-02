#include "system/String.h"
#include "system/SHA1.h"

/*
*	for reference, every instance of 0xFFFFFFFF is to maintain the word length at 32 bits
*/


namespace alk {

	cSHA1::cSHA1()
	{
		Reset();
	}

	cSHA1::~cSHA1()
	{
	}

	void cSHA1::Reset()
	{
		// define initial H vals
		H[0] = 0x67452301;
		H[1] = 0xEFCDAB89;
		H[2] = 0x98BADCFE;
		H[3] = 0x10325476;
		H[4] = 0xC3D2E1F0;
	}

	unsigned int cSHA1::ProcessMessage()
	{
		return 1;
	}

	////////////////////
	// ROTATION FUNCTIONS
	unsigned int ROTL(int N, unsigned int W)
	{
		return (W << N) & 0xFFFFFFFF | ((W & 0xFFFFFFFF) >> (32 - N));
	}

	unsigned int ROTR(int N, unsigned int W)
	{
		return (W >> N) & 0xFFFFFFFF | ((W & 0xFFFFFFFF) << (32 - N));
	}
}