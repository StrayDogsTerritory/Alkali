#ifndef ALK_MATRIX_H
#define ALK_MATRIX_H

// for translate
#include "math/Vector3.h"
#include "system/String.h"
#include <stdlib.h>

namespace alk {

	template<class T> 
	class cMatrix
	{
	public:
		union {
			T m[4][4];
			T v[16];
		};

		inline cMatrix() {}

		inline cMatrix(double* pA)
		{
			m[0][0] = (T)pA[0]; 
			m[0][1] = (T)pA[1]; 
			m[0][2] = (T)pA[2]; 
			m[0][3] = (T)pA[3];
			m[1][0] = (T)pA[4];
			m[1][1] = (T)pA[5];
			m[1][2] = (T)pA[6];
			m[1][3] = (T)pA[7];
			m[2][0] = (T)pA[8];
			m[2][1] = (T)pA[9];
			m[2][2] = (T)pA[10];
			m[2][3] = (T)pA[11];
			m[3][0] = (T)pA[12];
			m[3][1] = (T)pA[13];
			m[3][2] = (T)pA[14];
			m[3][3] = (T)pA[15];
		}
		cMatrix(T* pA)
		{
			// get to this later
		}

		cMatrix(T a00, T a01, T a02, T a03,
			T a10, T a11, T a12, T a13,
			T a20, T a21, T a22, T a23,
			T a30, T a31, T a32, T a33)
		{
			m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
			m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
			m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
			m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
		}

		inline cVector3<T> GetTranslate()
		{
			return cVector3<T>(m[0][3], m[1][3], m[2][3]);
		}

		inline void SetTranslate(const cVector3<T>& avX)
		{
			m[0][3] = avX.x;
			m[1][3] = avX.y;
			m[2][3] = avX.z;
		}

		inline cMatrix<T> GetRotation()
		{
			return cMatrix<T>(m[0][0], m[0][1], m[0][2], 0,
				m[1][0], m[1][1], m[1][2], 0,
				m[2][0], m[2][1], m[2][2], 0,
				0, 0, 0, 1);
		}

		inline cMatrix<T> GetTranspose()
		{
			return cMatrix<T>(m[0][0], m[1][0], m[2][0], m[3][0],
							  m[0][1], m[1][1], m[2][1], m[3][1],
							  m[0][2], m[1][2], m[2][2], m[3][2],
							  m[0][3], m[1][3], m[2][3], m[3][3]);
		}

		inline tString ToString() const
		{
			char buf[512];
			sprintf(buf, "[%f %f %f %f]\n[%f %f %f %f]\n[%f %f %f %f]\n[%f %f %f %f]",
				m[0][0], m[0][1], m[0][2], m[0][3],
				m[1][0], m[1][1], m[1][2], m[1][3],
				m[2][0], m[2][1], m[2][2], m[2][3],
				m[3][0], m[3][1], m[3][2], m[3][3]);
			return buf;
		}

		static const cMatrix<T> identity;
		static const cMatrix<T> zero;
		static const cMatrix<T> sign;
	};
		
	typedef cMatrix<float> tMatrixf;
}

#endif