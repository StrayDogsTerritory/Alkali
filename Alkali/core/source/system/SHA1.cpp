#include "system/SHA1.h"
#include "system/String.h"

namespace alk {

	//----------------------------------------------------------

	cSHA1::cSHA1()
	{
		Reset(); //reset values to initial
	}

	//----------------------------------------------------------

	cSHA1::~cSHA1()
	{
		//does nothing
	}

	//----------------------------------------------------------

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

	//----------------------------------------------------------

	tString cSHA1::Hash(const tString& asString)
	{
		Input((const unsigned char*)asString.c_str(), asString.size()); // take the size and data of a std::string for input

		PadMessage(); // pad message until a multiple of 512 bits is reached

		ProcessMessage(); // hash the message
		
		return Format(); // take the hashes, add them together and output the resulting string
	}

	//----------------------------------------------------------

	twString cSHA1::Hash(const twString& asString)
	{
		Input((const unsigned char*)cString::To8BitChar(asString).c_str(), cString::To8BitChar(asString).size());// convert the std::wstring to std::string, can introduce some issues with Unicode charaters, but it'll do for now.

		PadMessage();// pad message until a multiple of 512 bits is reached

		ProcessMessage();// hash the message

		return cString::ToWideChar(Format());// take the hashes, add them together, convert the std::string to a std::wstring, and output the resulting string
	}

	//----------------------------------------------------------

	void cSHA1::Input(const unsigned char* asMessage, unsigned int alLength)
	{
		while (alLength--) // for every character of the input word
		{
			
			mlLength+=8; // increment our length in bits, used for padding the last bytes of the message before we hash.
			if (mlLength == 0)
			{
				// do nothing for now, if it's 0 there been an overflow, which means the length of the message has exceeded 2^32, since I've elected to ignore messages that size, it won't matter
			}

			mlMessageBlock[mlMessageBlockIndex++] = (*asMessage ); //message block at the index is equal to the specific character of the original string

			if (mlMessageBlockIndex == 64) // if the message is perfectly filled up before we even need to compute it
			{
				ProcessMessage(); // hash it
			}

			asMessage++; // get the next char
		}
	}

	//----------------------------------------------------------

	void cSHA1::PadMessage()
	{
		/*
		* If the message is too long, we'll need to pad some amount of bits into a
		* seperate message block
		*/
		if (mlMessageBlockIndex > 55)
		{
			mlMessageBlock[mlMessageBlockIndex++] = 0x80; // set the next bit equal to 1 in ASCII

			while (mlMessageBlockIndex < 64)
			{
				mlMessageBlock[mlMessageBlockIndex++] = 0x0; // appened 0s until we wreach 512 bits
			}

			ProcessMessage(); // since the message is too long, we need to hash it now

			while (mlMessageBlockIndex < 56) // loop is reset to 0 in PadMessage(), so pad with 0s again until we can store length in the last 8 bytes. Note though that this isn't technically good, since this can't properly process messages 2^32 in length, but whatever.
			{
				mlMessageBlock[mlMessageBlockIndex++] = 0x0; // appened 0s until we wreach 512 bits
			}
		}
		else // <512 bit message size, so just pad until 512 bits are present
		{
			mlMessageBlock[mlMessageBlockIndex++] = 0x80;// set the next bit equal to 1 in ASCII

			while (mlMessageBlockIndex < 56) 
			{
				mlMessageBlock[mlMessageBlockIndex++] = 0x0;// appened 0s until we wreach 512 bits
			}
		}

		// store the length in the last 8 bytes. Should technically have more going here but if the message exceeds 2^32 bits in length there comes a point where you just take it on the chin and be wrong
		mlMessageBlock[56] = 0;//appened 0
		mlMessageBlock[57] = 0;//appened 0
		mlMessageBlock[58] = 0;//appened 0
		mlMessageBlock[59] = 0;//appened 0
		mlMessageBlock[60] = (mlLength >> 24) & 0xFF; //appened first 2 bytes of length 
		mlMessageBlock[61] = (mlLength >> 16) & 0xFF;//appened middle 2 bytes of length 
		mlMessageBlock[62] = (mlLength >> 8) & 0xFF;//appened next set of middle 2 bytes of length 
		mlMessageBlock[63] = (mlLength) & 0xFF;//appened last 2 bytes of length
	}

	//----------------------------------------------------------

	void cSHA1::ProcessMessage()
	{

		int t=0; // loop counter
		unsigned int A, B, C, D, E; // working vars
		unsigned int W[80]; // 512-bit message schedule
		unsigned int ltemp; // temporary buffer. As specified by FIPS 180-4

		// setup constants. These are defined in SHS 180-4
		const unsigned int K[] = {
			0x5a827999,
			0x6ed9eba1,
			0x8f1bbcdc,
			0xca62c1d6
		};

		// initialize the message schedule
		for (t=0; t < 16; t++)
		{
			W[t] = ((unsigned int)mlMessageBlock[t * 4]) << 24; // add first byte to the schedule
			W[t] |= ((unsigned int)mlMessageBlock[t * 4 + 1]) << 16;// add second byte to the schedule
			W[t] |= ((unsigned int)mlMessageBlock[t * 4 + 2]) << 8;// add third byte to the schedule
			W[t] |= ((unsigned int)mlMessageBlock[t * 4 + 3]);// add fourth byte to the schedule
		}

		for (t=16; t < 80; t++)
		{
			W[t] = ROTL((W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]), 1); // just do this I guess. FIPS demands it to initialize the last 56 bytes of the schedule. I'm not a cryptography expert, but I reckon it makes it more secure. 
		}

		// initialize working variables
		A = H[0]; 
		B = H[1];
		C = H[2];
		D = H[3];
		E = H[4];

		/*
			 looping through hashing functions
			function names are provided as they are named in FIPS 180-4

			Fair warning: Understanding the *why* behind these function is way above my pay-grade (and probably my security clearance level).
			If the following seems logically confusing -yeah me too.

			Interesting fact:
			Most of the algorithm is identical between different loops, save for which constant K is being used, and the function ltemp is being set to first.
		*/
		
		for (t = 0; t < 20; t++) // Choose function
		{
			ltemp = ROTL(A, 5) + ((B & C) ^ ((~B) & D)) + E + K[0] + W[t];
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = ltemp;
		}

		for (t=20; t < 40; t++) // Parity function
		{
			ltemp = ROTL(A, 5) + (B ^ C ^ D) + E + K[1] + W[t];
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = ltemp;
		}

		for (t = 40; t < 60; t++) // Majority function
		{
			ltemp = ROTL(A, 5) + ((B & C) ^ (B & D) ^ (C & D)) + E + K[2] + W[t];
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = ltemp;
		}
		
		for (t = 60; t < 80; t++) // Parity function, again
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

		mlMessageBlockIndex = 0; //reset the index for repadding long messages
	}

	//----------------------------------------------------------

	tString cSHA1::Format() const
	{
		tString sRet = ""; // initialize a std::string to return
		char buf[16]; // create some stack memory for a buffer
		for (int i = 0; i < 5; i++) // for every hash value
		{
			sprintf(buf, "%08x", H[i]); // format bytes into character buffer
			sRet += buf; // add the created formatted bytes to the string
		}

		return sRet;
	}

	//----------------------------------------------------------

	unsigned int cSHA1::ROTL(unsigned int W, unsigned int N)
	{
		/*
		* kinda hard to explain well, so it gets the big comment
		* shifts the word, W by N bits,
		* then it ORs it with W shifted by word length subtracted by N.
		* Hope that helps!
		*/

		return ((W << N)) | ((W) >> (32 - N));
	}

	//----------------------------------------------------------
}