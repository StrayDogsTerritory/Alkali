#include "math/Quaternion.h"
#include "math/Vector3.h"

#include <math.h>

namespace alk {

	cQuaternion::cQuaternion()
	{
		v = 0;
		w = 0;
	}

	cQuaternion::cQuaternion(float afX)
	{
		v = afX;
		w = afX;
	}

	cQuaternion::cQuaternion(float afX, float afW)
	{
		v = afX;
		w = afW;
	}

	cQuaternion::cQuaternion(float afAngle, cVector3<float> avAxis)
	{
		FromAxisAngle(afAngle, avAxis);
	}

	cQuaternion::cQuaternion(float afX, float afY, float afZ, float afW)
	{
		v.x = afX;
		v.y = afY;
		v.z = afZ;
		w = afW;
	}



	void cQuaternion::FromAxisAngle(float afAngle, cVector3<float> avAxis)
	{
		float fHlfAngle = afAngle * 0.5;
		float HlfSin = sin(fHlfAngle);
		float HlfCos = cos(fHlfAngle);

		w = HlfCos;
		v.x = HlfSin * avAxis.x;
		v.y = HlfSin * avAxis.y;
		v.z = HlfSin * avAxis.z;
	}

	void cQuaternion::ToRotationMatrix(tMatrixf& amDestMtx)
	{
		tMatrixf mOutMatrix;

		float f2X = 2.0f * v.x;
		float f2Y = 2.0f * v.y;
		float f2Z = 2.0f * v.z;

		float fXX = f2X * v.x;
		float fXY = f2X * v.y;
		float fXZ = f2X * v.z;
		float fXW = f2X * w;
		float fYY = f2Y * v.y;
		float fYZ = f2Y * v.z;
		float fYW = f2Y * w;
		float fZZ = f2Z * v.z;
		float fZW = f2Z * w;

		amDestMtx.m[0][0] = 1.0f - (fYY + fZZ);
		amDestMtx.m[0][1] = fXZ - fZW;
		amDestMtx.m[0][2] = fXZ + fYW;
		amDestMtx.m[1][0] = fXY + fZW;
		amDestMtx.m[1][1] = 1.0f - (fXX + fZZ);
		amDestMtx.m[1][2] = fYZ - fXW;
		amDestMtx.m[2][0] = fXZ - fYW;
		amDestMtx.m[2][1] = fYZ + fXW;
		amDestMtx.m[2][2] = 1.0f - (fXX + fYY);
	}
	void cQuaternion::FromRotationMatrix(const tMatrixf amtxA)
	{

	}
}