#include "math/Math.h"

#include "system/Platform.h"

#include <stdlib.h>
#include <time.h>

namespace alk {

	int cMath::Rand(int alMin, int alMax, int alSeed)
	{
		SeededRand(alSeed);
		return (rand()%(alMax-alMin+1))+alMin;
	}

	float cMath::Rand(float afMin, float afMax)
	{
		SeededRand(0);
		float fRand = ((float)rand()) / (float)RAND_MAX;
		return afMin + fRand*(afMax - afMin);
	}

	tVector2f cMath::Rand(tVector2f afMin, tVector2f afMax)
	{
		return tVector2f(Rand(afMin.x, afMax.y),
						 Rand(afMin.x, afMin.y));
	}

	tVector3f cMath::Rand(tVector3f afMin, tVector3f afMax)
	{
		return tVector3f(Rand(afMin.x, afMax.x),
						 Rand(afMin.y, afMax.y),
						 Rand(afMin.z, afMax.z));
	}

	cColour cMath::Rand(cColour acMin, cColour acMax)
	{
		return cColour(Rand(acMin.r, acMax.r),
					   Rand(acMin.g, acMax.g),
					   Rand(acMin.b, acMax.b),
					   Rand(acMin.a, acMax.a));
	}

	void cMath::SeededRand(size_t alSeed)
	{
		if (alSeed == 0)
			srand((unsigned int)(cPlatform::GetSysUpTime() % (cPlatform::GetAppTime() + 1)));
		else
		srand((unsigned int)alSeed);
	}

	float cMath::clamp(float afX, float afMin, float afMax) 
	{
		if (afX < afMin) afX = afMin;
		if (afX > afMax) afX = afMax;
		return afX;
	}

	int cMath::clamp(int alX, int alMin, int alMax)
	{
		if (alX < alMin) alX = alMin;
		if (alX > alMax) alX = alMax;
		return alX;
	}

	///////////////////
	// vector

	float cMath::Vector3Dot(const tVector3f& avA, const tVector3f& avB)
	{
		return (avA.x * avB.x + avA.y * avB.y + avA.z * avB.z);
	}

	tVector3f cMath::Vector3Cross(const tVector3f& avA, const tVector3f& avB)
	{
		tVector3f avTemp;
		avTemp.x = (avA.y * avB.z - avA.z * avB.y);
		avTemp.y = (avA.z * avB.x - avA.x * avB.z);
		avTemp.z = (avA.x * avB.y - avA.y * avB.x);
		return avTemp;
	}

	///////////////////
	// matrix
	tMatrixf cMath::MatrixMul(const tMatrixf& aA, const tMatrixf& aB)
	{
		tMatrixf mResult;
		mResult.m[0][0] = aA.m[0][0] * aB.m[0][0] + aA.m[0][1] * aB.m[1][0] + aA.m[0][2] * aB.m[2][0] + aA.m[0][3] * aB.m[3][0];
		mResult.m[0][1] = aA.m[0][0] * aB.m[0][1] + aA.m[0][1] * aB.m[1][1] + aA.m[0][2] * aB.m[2][1] + aA.m[0][3] * aB.m[3][1];
		mResult.m[0][2] = aA.m[0][0] * aB.m[0][2] + aA.m[0][1] * aB.m[1][2] + aA.m[0][2] * aB.m[2][2] + aA.m[0][3] * aB.m[3][2];
		mResult.m[0][3] = aA.m[0][0] * aB.m[0][3] + aA.m[0][1] * aB.m[1][3] + aA.m[0][2] * aB.m[2][3] + aA.m[0][3] * aB.m[3][3];

		mResult.m[1][0] = aA.m[1][0] * aB.m[0][0] + aA.m[1][1] * aB.m[1][0] + aA.m[1][2] * aB.m[2][0] + aA.m[1][3] * aB.m[3][0];
		mResult.m[1][1] = aA.m[1][0] * aB.m[0][1] + aA.m[1][1] * aB.m[1][1] + aA.m[1][2] * aB.m[2][1] + aA.m[1][3] * aB.m[3][1];
		mResult.m[1][2] = aA.m[1][0] * aB.m[0][2] + aA.m[1][1] * aB.m[1][2] + aA.m[1][2] * aB.m[2][2] + aA.m[1][3] * aB.m[3][2];
		mResult.m[1][3] = aA.m[1][0] * aB.m[0][3] + aA.m[1][1] * aB.m[1][3] + aA.m[1][2] * aB.m[2][3] + aA.m[1][3] * aB.m[3][3];

		mResult.m[2][0] = aA.m[2][0] * aB.m[0][0] + aA.m[2][1] * aB.m[1][0] + aA.m[2][2] * aB.m[2][0] + aA.m[2][3] * aB.m[3][0];
		mResult.m[2][1] = aA.m[2][0] * aB.m[0][1] + aA.m[2][1] * aB.m[1][1] + aA.m[2][2] * aB.m[2][1] + aA.m[2][3] * aB.m[3][1];
		mResult.m[2][2] = aA.m[2][0] * aB.m[0][2] + aA.m[2][1] * aB.m[1][2] + aA.m[2][2] * aB.m[2][2] + aA.m[2][3] * aB.m[3][2];
		mResult.m[2][3] = aA.m[2][0] * aB.m[0][3] + aA.m[2][1] * aB.m[1][3] + aA.m[2][2] * aB.m[2][3] + aA.m[2][3] * aB.m[3][3];

		mResult.m[3][0] = aA.m[3][0] * aB.m[0][0] + aA.m[3][1] * aB.m[1][0] + aA.m[3][2] * aB.m[2][0] + aA.m[3][3] * aB.m[3][0];
		mResult.m[3][1] = aA.m[3][0] * aB.m[0][1] + aA.m[3][1] * aB.m[1][1] + aA.m[3][2] * aB.m[2][1] + aA.m[3][3] * aB.m[3][1];
		mResult.m[3][2] = aA.m[3][0] * aB.m[0][2] + aA.m[3][1] * aB.m[1][2] + aA.m[3][2] * aB.m[2][2] + aA.m[3][3] * aB.m[3][2];
		mResult.m[3][3] = aA.m[3][0] * aB.m[0][3] + aA.m[3][1] * aB.m[1][3] + aA.m[3][2] * aB.m[2][3] + aA.m[3][3] * aB.m[3][3];
		return mResult;
	}

}