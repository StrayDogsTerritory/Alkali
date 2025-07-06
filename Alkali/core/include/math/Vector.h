#ifndef ALK_VECTOR_H
#define ALK_VECTOR_H

#include "math.h"

namespace alk {

	//========================================
	// |||||||||||||||||||||||||||||||||||||||
	//----------------------------------------
	// Vector3
	//-----------------------------------------
	// |||||||||||||||||||||||||||||||||||||||
	//========================================

	template <class T> class cVector2
	{
	public:
		struct
		{
			T x, y;
		};

		////////////////////////////////
		//constructors

		cVector2() : x(0), y(0)
		{
		}

		cVector2(T ax, T ay)
			: x(ax), y(ay)
		{
		}

		cVector2(T axy)
			: x(axy), y(axy)
		{
		}

		cVector2(const cVector2<T>& avector)
			: x(avector.x), y(avector.y)
		{
		}

		////////////////////////////////
		// operators

		inline cVector2<T>& operator=(const cVector2<T>& avector)
		{
			x = avector.x;
			y = avector.y;

			return *this;
		}

		inline cVector2<T>& operator=(const T& aVal)
		{
			x = aVal;
			y = aVal;
			return *this;
		}
		//------------------------------------------

		inline cVector2<T> operator+(const cVector2<T>& avector) const
		{
			cVector2<T> vVec;

			vVec.x = x + avector.x;
			vVec.y = y + avector.y;

			return vVec;
		}

		inline cVector2<T> operator+(const T &aVal) const
		{
			cVector2<T> vVec;

			vVec.x = x + aVal;
			vVec.y = y + aVal;

			return vVec;
		}

		//------------------------------------------

		inline cVector2<T> operator-(const cVector2<T>& avector) const
		{
			cVector2<T> vVec;
			vVec.x = x - avector.x;
			vVec.y = y - avector.y;
			return vVec;
		}
			
		inline cVector2<T> operator-(const T& aVal) const
		{
			cVector2<T> vVec;

			vVec.x = x + aVal;
			vVec.y = y + aVal;

			return vVec;
		}

		//------------------------------------------

		inline cVector2<T> operator*(const T& aVal) const
		{
			cVector2<T> vVec;
			vVec.x = x * aVal;
			vVec.y = y * aVal;
			return vVec;
		}

		inline cVector2<T> operator*(const cVector2<T>& avector) const
		{
			cVector2<T> vVec;
			vVec.x = x * avector.x;
			vVec.y = y * avector.y;
			return vVec;
		}

		//------------------------------------------

		inline cVector2<T> operator/(const T& aVal) const
		{
			cVector2<T> vVec;
			vVec.x = x / aVal;
			vVec.y = y / aVal;
			return vVec;
		}

		inline cVector2<T> operator/(const cVector2<T>& avector) const
		{
			cVector2<T> vVec;
			vVec.x = x / avector.x;
			vVec.y = y / avector.y;
			return vVec;
		}

		//------------------------------------------

		inline cVector2<T>& operator+=(const cVector2<T>& avector)
		{
			x += avector.x;
			y += avector.y;
			return *this;
		}

		inline cVector2<T>& operator+=(const T& aVal)
		{
			x += aVal;
			y += aVal;
			return *this;
		}

		//------------------------------------------

		inline cVector2<T>& operator-=(const cVector2<T>& avector)
		{
			x -= avector.x;
			y -= avector.y;
			return *this;
		}

		inline cVector2<T>& operator-=(const T& aVal)
		{
			x -= avector.x;
			y -= avector.y;
			return *this;
		}

		//------------------------------------------

		inline cVector2<T>& operator*=(const T& aVal)
		{
			x *= aVal;
			y *= aVal;
			return *this;
		}

		inline cVector2<T>& operator*=(const cVector2<T>& aVector)
		{
			x *= avector.x;
			y *= avector.y;
			return *this;
		}

		//------------------------------------------

		inline cVector2<T>& operator/=(const T& aVal)
		{
			x /= aVal;
			y /= aVal;
			return *this;
		}

		inline cVector2<T>& operator/=(const cVector2<T>& aVector)
		{
			x /= avector.x;
			y /= avector.y;
			return *this;
		}

		//------------------------------------------

		inline bool operator==(const cVector2<T>& avector) const
		{
			if (x == avector.x && y == avector.y)
				return true;
			else
				return false;
		}

		inline bool operator!=(const cVector2<T>& avector) const
		{
			if (x == avector.x && y == avector.y)
				return false;
			else
				return true;
		}

		///////////////////////////////
		// methods

		T Length() const
		{
			return sqrt(x * x + y * y);
		}

		T LengthSquared() const
		{
			return (x * x + y * y);
		}

		T Normalize()
		{ 
			T xLength = sqrt(x * x + y * y);

			T xLengthInv = 1.0f / xLength;

			x *= xLengthInv;
			y *= xLengthInv;
		}
	};



	//========================================
	// |||||||||||||||||||||||||||||||||||||||
	//----------------------------------------
	// Vector3
	//-----------------------------------------
	// |||||||||||||||||||||||||||||||||||||||
	//========================================



	template <class T> 
	class cVector3
	{
	public:
		struct
		{
			T x, y, z;
		};

		////////////////////////////////
		//constructors

		cVector3() : x(0), y(0), z(0)
		{
		}

		cVector3(T ax, T ay, T az)
			: x(ax), y(ay), z(az)
		{
		}

		cVector3(T axyz)
			: x(axyz), y(axyz), z(axyz)
		{
		}

		////////////////////////////////
		// operators

		inline cVector3<T>& operator=(const cVector3<T>& avector)
		{
			x = avector.x;
			y = avector.y;
			z = avector.z;
			return *this;
		}

		inline cVector3<T>& operator=(const T& aVal)
		{
			x = aVal;
			y = aVal;
			z = aVal;
			return *this;
		}

		//------------------------------------------

		inline cVector3<T> operator+(const cVector3<T>& avector) const
		{
			cVector3<T> vVec;
			vVec.x = x + avector.x;
			vVec.y = y + avector.y;
			vVec.z = z + avector.z;
			return vVec;
		}

		inline cVector3<T> operator+(const T& aVal) const
		{
			cVector3<T> vVec;
			vVec.x = x + aVal;
			vVec.y = y + aVal;
			vVec.z = z + aVal;
			return vVec;
		}

		//------------------------------------------

		inline cVector3<T> operator-(const cVector3<T>& avector) const
		{
			cVector3<T> vVec;
			vVec.x = x - avector.x;
			vVec.y = y - avector.y;
			vVec.z = z - avector.z;
			return vVec;
		}

		inline cVector3<T> operator-(const T& aVal) const
		{
			cVector3<T> vVec;
			vVec.x = x - aVal;
			vVec.y = y - aVal;
			vVec.z = z - aVal;
			return vVec;
		}

		//------------------------------------------

		inline cVector3<T> operator*(const cVector3<T>& avector) const
		{
			cVector3<T> vVec;
			vVec.x = x * avector.x;
			vVec.y = y * avector.y;
			vVec.z = z * avector.z;
			return vVec;
		}

		inline cVector3<T> operator*(const T& aVal) const
		{
			cVector3<T> vVec;
			vVec.x = x * aVal;
			vVec.y = y * aVal;
			vVec.z = z * aVal;
			return vVec;
		}

		//------------------------------------------

		inline cVector3<T> operator/(const cVector3<T>& avector) const
		{
			cVector3<T> vVec;
			vVec.x = x / avector.x;
			vVec.y = y / avector.y;
			vVec.z = z / avector.z;
			return vVec;
		}

		inline cVector3<T> operator/(const T& aVal) const
		{
			cVector3<T> vVec;
			vVec.x = x / aVal;
			vVec.y = y / aVal;
			vVec.z = z / aVal;
			return vVec;
		}

		//------------------------------------------

		inline cVector3<T>& operator+=(const cVector3<T>& avector)
		{
			x += avector.x;
			y += avector.y;
			z += avector.z;
			return *this;
		}

		inline cVector3<T>& operator+=(const T& aVal)
		{
			x += aVal;
			y += aVal;
			z += aVal;
			return *this;
		}

		//------------------------------------------

		inline cVector3<T>& operator-=(const cVector3<T>& avector)
		{
			x -= avector.x;
			y -= avector.y;
			z -= avector.z;
			return *this;
		}

		inline cVector3<T>& operator-=(const T& aVal)
		{
			x -= aVal;
			y -= aVal;
			z -= aVal;
			return *this;
		}

		//------------------------------------------

		inline cVector3<T>& operator*=(const cVector3<T>& avector)
		{
			x *= avector.x;
			y *= avector.y;
			z *= avector.z;
			return *this;
		}

		inline cVector3<T>& operator*=(const T& aVal)
		{
			x *= aVal;
			y *= aVal;
			z *= aVal;
			return *this;
		}

		//------------------------------------------

		inline cVector3<T>& operator/=(const cVector3<T>& avector)
		{
			x /= avector.x;
			y /= avector.y;
			z /= avector.z;
			return *this;
		}

		inline cVector3<T>& operator/=(const T& aVal)
		{
			x /= aVal;
			y /= aVal;
			z /= aVal;
			return *this;
		}

		//------------------------------------------

		inline bool operator==(const cVector3<T>& avector) const
		{
			if (x == avector.x && y == avector.y && z == avector.z)
				return true;
			else
				return false;
		}

		inline bool operator!=(const cVector3<T>& avector) const
		{
			if (x == avector.x && y == avector.y && z == avector.z)
				return false;
			else
				return true;
		}

		//------------------------------------------

		///////////////////////////////
		// methods

		T Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		T LengthSquared() const
		{
			return (x * x + y * y + z * z);
		}

		T Normalize()
		{
			T xLength = sqrt(x * x + y * y + z * z);
			
			T xLengthInv = 1.0f / xLength;
			x *= xLengthInv;
			y *= xLengthInv;
			z *= xLengthInv;
			return xLengthInv;
		}

	};
	



}
#endif