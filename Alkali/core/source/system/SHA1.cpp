#include "system/SHA1.h"
#include "system/String.h"

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
		// init internal vars
		mlMessageBlockIndex = 0;
		mlLength = 0;
		// set H[i] to their inital values, as defined in FIPS 180-4
		H[0] = 0x67452301;
		H[1] = 0xefcdab89;
		H[2] = 0x98badcfe;
		H[3] = 0x10325476;
		H[4] = 0xc3d2e1f0;
	}

	tString cSHA1::Hash(const tString& asString)
	{
		Input((const unsigned char*)asString.c_str(), asString.size());

		PadMessage();

		ProcessMessage();
		
		return Format();
	}

	twString cSHA1::Hash(const twString& asString)
	{
		Input((const unsigned char*)cString::To8BitChar(asString).c_str(), cString::To8BitChar(asString).size());

		PadMessage();

		ProcessMessage();

		return cString::ToWideChar(Format());
	}

	void cSHA1::Input(const unsigned char* asMessage, unsigned int alLength)
	{
		while (alLength--)
		{
			
			mlLength+=8;
			if (mlLength == 0)
			{
				// do nothing for now
			}

			mlMessageBlock[mlMessageBlockIndex++] = (*asMessage );

			if (mlMessageBlockIndex == 64)
			{
				ProcessMessage();
			}

			asMessage++;
		}
	}

	void cSHA1::PadMessage()
	{
		/*
		* If the message is too long, we'll need to pad into a
		* seperate message block
		*/
		if (mlMessageBlockIndex > 55)
		{
			mlMessageBlock[mlMessageBlockIndex++] = 0x80;

			while (mlMessageBlockIndex < 64)
			{
				mlMessageBlock[mlMessageBlockIndex++] = 0x0;
			}

			ProcessMessage();

			while (mlMessageBlockIndex < 56)
			{
				mlMessageBlock[mlMessageBlockIndex++] = 0x0;
			}
		}
		else //otherwise just pad until we reach 448 bits 
		{
			mlMessageBlock[mlMessageBlockIndex++] = 0x80;

			while (mlMessageBlockIndex < 56)
			{
				mlMessageBlock[mlMessageBlockIndex++] = 0x0;
			}
		}

		// store the length in the last 8 bytes.
		mlMessageBlock[56] = 0;
		mlMessageBlock[57] = 0;
		mlMessageBlock[58] = 0;
		mlMessageBlock[59] = 0;
		mlMessageBlock[60] = (mlLength >> 24) & 0xFF;
		mlMessageBlock[61] = (mlLength >> 16) & 0xFF;
		mlMessageBlock[62] = (mlLength >> 8) & 0xFF;
		mlMessageBlock[63] = (mlLength) & 0xFF;
	}

	void cSHA1::ProcessMessage()
	{

		int t=0; // loop counter
		unsigned int A, B, C, D, E; // working vars
		unsigned int W[80]; // 512-bit message schedule
		unsigned int ltemp; // temporary buffer. As specified by FIPS 180-4

		// setup constants
		const unsigned int K[] = {
			0x5a827999,
			0x6ed9eba1,
			0x8f1bbcdc,
			0xca62c1d6
		};

		// initialize the message schedule
		for (t=0; t < 16; t++)
		{
			W[t] = ((unsigned int)mlMessageBlock[t * 4]) << 24;
			W[t] |= ((unsigned int)mlMessageBlock[t * 4 + 1]) << 16;
			W[t] |= ((unsigned int)mlMessageBlock[t * 4 + 2]) << 8;
			W[t] |= ((unsigned int)mlMessageBlock[t * 4 + 3]);
		}

		for (t=16; t < 80; t++)
		{
			W[t] = ROTL((W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]), 1);
		}

		// initialize working variables
		A = H[0];
		B = H[1];
		C = H[2];
		D = H[3];
		E = H[4];

		// looping through hashing functions
		// function names are provided as they are named in FIPS 180-4
		for (t = 0; t < 20; t++) // choose
		{
			ltemp = ROTL(A, 5) + ((B & C) ^ ((~B) & D)) + E + K[0] + W[t];
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = ltemp;
		}

		for (t=20; t < 40; t++) // parity
		{
			ltemp = ROTL(A, 5) + (B ^ C ^ D) + E + K[1] + W[t];
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = ltemp;
		}

		for (t = 40; t < 60; t++) // majority
		{
			ltemp = ROTL(A, 5) + ((B & C) ^ (B & D) ^ (C & D)) + E + K[2] + W[t];
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = ltemp;
		}
		
		for (t = 60; t < 80; t++) // parity
		{
			ltemp = ROTL(A, 5) + (B ^ C ^ D) + E + K[3] + W[t];
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = ltemp;
		}

		// final setting of the hash values
		H[0] = A + H[0];
		H[1] = B + H[1];
		H[2] = C + H[2];
		H[3] = D + H[3];
		H[4] = E + H[4];

		mlMessageBlockIndex = 0;
	}



	tString cSHA1::Format() const
	{
		tString sRet = "";
		char buf[16];
		for (int i = 0; i < 5; i++)
		{
			sprintf(buf, "%08x", H[i]);
			sRet += buf;
		}

		return sRet;
	}

	unsigned int cSHA1::ROTL(unsigned int W, unsigned int N)
	{
		return ((W << N)) | ((W) >> (32 - N));
	}


}