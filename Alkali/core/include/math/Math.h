#ifndef ALK_MATH_H
#define ALK_MATH_H

#include <math.h>
#include <vector>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"

#include "graphics/Colour.h"

namespace alk {
	
	// math constants 
	#define kPI (3.141592654f)
	#define k2PIf (1.570796327f)
	#define kPI2f (6.283185307f)

	#define kEpsilonf (0.00001f) 
	#define ksqrt2f (1.414213562f)

	class cMath
	{
	public:

		static int Rand( int alMin, int alMax, int alSeed = 0);
		static float Rand( float afMin, float afMax);
		static tVector2f Rand(tVector2f afMin, tVector2f afMax);
		static tVector3f Rand(tVector3f afMin, tVector3f afMax);
		static cColour Rand(cColour acMin, cColour acMax);

		static void SeededRand(size_t alSeed);

		static int clamp(int alX, int alMin, int alMax);
		static float clamp(float afX, float afMin, float afMax);

		inline static int abs(int alVal) { return abs(alVal); }
		inline static float abs(float afVal) { return fabs(afVal); }

		static int Wrap(int alX, int alMin, int alMax);
		static float Wrap(float afX, float afMin, float afMax);

		static int Lerp(int alA, int alB, int alT);
		static float Lerp(float afA, float afB, float afT);

		static float ToDeg(float afAngle);
		static float ToRad(float afAngle);

		/////////////////////////////
		// vector2 functions
		////////////////////////////

		/////////////////////////////
		// vector3 functions
		////////////////////////////
		static float Vector3Dot(const tVector3f& avA, const tVector3f& avB);
		static tVector3f Vector3Cross(const tVector3f& avA, const tVector3f& avB);
		static tVector3f Vector3Project(const tVector3f& avA, const tVector3f& avB);
		static tVector3f Vector3Reject(const tVector3f& avA, const tVector3f& avB);
		/////////////////////////////
		// matrix functions
		////////////////////////////

		static tMatrixf MatrixMul(const tMatrixf& aA, const tMatrixf& aB);
		static tVector3f MatrixMul(const tVector3f& avX, const tMatrixf& aB);
		static tMatrixf MatrixMul(float afX, const tMatrixf& aB);

		static tMatrixf MatrixInverse(const tMatrixf& aA);
		static tMatrixf MatrixAdjoint(const tMatrixf& aA);

		static float MatrixDeterminant(const tMatrixf& aA);
		static float MatrixMinor(const tMatrixf& aA, int r1, int r2, int r3, int c1, int c2, int c3);

		static tMatrixf RotateX(float afAngle);
		static tMatrixf RotateY(float afAngle);
		static tMatrixf RotateZ(float afAngle);

	};
}
#endif
