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
		mlMessageBlockIndex = 0;

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

		char* sRet = Format();

		return tString(sRet);
	}

	twString cSHA1::Hash(const twString& asString)
	{
		tString sString = cString::To8BitChar(asString);

		Input((const unsigned char*)sString.c_str(), sString.size());

		PadMessage();

		ProcessMessage();

		return cString::ToWideChar(Format());
	}

	void cSHA1::Input(const unsigned char* asMessage, unsigned int alLength)
	{
		while (alLength--)
		{
			if (mlMessageBlockIndex == 64)
			{
				ProcessMessage();
			}

			mlMessageBlock[mlMessageBlockIndex] = (*asMessage &0xFF);

			asMessage++;
			mlMessageBlockIndex++;
		}
	}

	void cSHA1::PadMessage()
	{

	}

	void cSHA1::ProcessMessage()
	{
		int t;
		unsigned int A, B, C, D, E;
		unsigned int W[80];

		for (t = 0; t < 16; ++t)
		{
			W[t] = ((unsigned int)mlMessageBlockIndex[t * 4]) << 24;
		}

	}

	char* cSHA1::Format() const
	{
		char* sRet = "";
		for (int i = 0; i < 4; ++i)
		{
			sRet += sprintf(sRet, "%08x", H[i]);
		}

		return sRet;
	}


}