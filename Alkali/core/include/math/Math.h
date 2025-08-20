#ifndef ALK_MATH_H
#define ALK_MATH_H

#include <math.h>

namespace alk {
	
	// math constants 
	#define kPIf (3.141592654f)
	#define k2PIf (1.570796327f)
	#define kPI2f (6.283185307f)

	#define kEpsilonf (0.00001f) 
	#define ksqrt2f (1.414213562f)


	class cMath
	{
	public:

		inline static tVector3f cross(tVector3f avX, tVector3f avY);

		static int Randl(int alMin, int alMax);
		static float Randf(float alMin, float alMax);

		static float clamp(float afMin, float afMax);

		inline static int abs(int alVal) { return abs(alVal); }
		inline static float fabs(float afVal) { return fabs(afVal); }
	};
}
#endif
