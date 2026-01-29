#ifndef ALK_QUATERNION_H
#define ALK_QUATERNION_H

#include "math/Vector3.h"
#include "math/Matrix.h"

namespace alk {


	class cQuaternion
	{
	public:
		cQuaternion();
		cQuaternion(float afX);
		cQuaternion(float afX, float afW);
		cQuaternion(float afAngle, cVector3<float> avAxis);
		cQuaternion(float afX, float afY, float afZ, float afW);

		cVector3<float> v;
		float w;

		void FromAxisAngle(float afAngle, cVector3<float> avAxis);
		
		void ToRotationMatrix(tMatrixf& amDestMtx);
		void FromRotationMatrix(const tMatrixf amtxA);

		tString ToString()
		{
			char buf[256];
			sprintf(buf, "[i: %f, j: %f, k: %f, w: %f]", v.x, v.y, v.z, w);
				return tString(buf);
		}
		

	};
}
#endif
