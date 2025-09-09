#ifndef ALK_VECTOR3_H
#define ALK_VECTOR3_H

#include "math/Vector2.h"

namespace alk {

	template<class T>
	class cVector3
	{
	public:
		union {
			struct {
				T x, y, z;
			};
			T v[3];
		};

		inline cVector3<T>& operator=(const cVector3<T>& avVec) {

			x = avVec.x; y = avVec.y; z = avVec.z;
			return *this;
		}

		inline cVector3<T>& operator=(const T atX) {
			x = atX; y = atX; z = atX;
			return *this;
		}

		inline cVector3<T>& operator==(const cVector3<T>& avVec) const {
			if (x == avVec.x && y == avVec.y && z == avVec.z) return true;
			else return false;
		}

		inline cVector3<T>& operator>(const cVector3<T>& avVec) const {
			if (x > avVec.x && y > avVec.y && z > avVec.z) return true;
			else return false;
		}

		inline cVector3<T>& operator<(const cVector3<T>& avVec) const {
			if (x < avVec.x && y < avVec.y && z < avVec.z) return true;
			else return false;
		}

		inline cVector3<T>& operator!=(const cVector3<T>& avVec) const {
			if (x == avVec.x && y == avVec.y && z == avVec.z) return false;
			else return true;
		}

		inline cVector3<T>& operator+(const cVector3<T>& avVec) const {
			cVector3<T> vVec;
			vVec.x = x + avVec.x;
			vVec.y = y + avVec.y;
			vVec.z = z + avVec.z;
			return vVec;
		}

		inline cVector3<T>& operator-(const cVector3<T>& avVec) const {
			cVector3<T> vVec;
			vVec.x = x - avVec.x;
			vVec.y = y - avVec.y;
			vVec.z = z - avVec.z;
			return vVec;
		}

		inline cVector3<T>& operator*(const cVector3<T> avVec) const {
			cVector3<T> vVec;
			vVec.x = x * avVec.x;
			vVec.y = y * avVec.y;
			vVec.z = z * avVec.z;
			return vVec;
		}

		inline cVector3<T>& operator/(const cVector3<T> avVec) const {
			cVector3<T> vVec;
			vVec.x = x / avVec.x;
			vVec.y = y / avVec.y;
			vVec.z = z / avVec.z;
			return vVec;
		}

		inline cVector3<T>& operator+(const T atX) const {
			cVector3<T> vVec;
			vVec.x = x + atX;
			vVec.y = y + atX;
			vVec.z = z + atX;
			return vVec;
		}

		inline cVector3<T>& operator-(const T atX) const {
			cVector3<T> vVec;
			vVec.x = x - atX;
			vVec.y = y - atX;
			vVec.z = z - atX;
			return vVec;
		}

		inline cVector3<T>& operator*(const T atX) const {
			cVector3<T> vVec;
			vVec.x = x * atX;
			vVec.y = y * atX;
			vVec.z = z * atX;
			return vVec;
		}

		inline cVector3<T>& operator/(const T atX) const {
			cVector3<T> vVec;
			vVec.x = x / atX;
			vVec.y = y / atX;
			vVec.z = z / atX;
			return vVec;
		}

		inline cVector3<T>& operator+=(const cVector3<T>& avVec) const {
			x += avVec.x;
			y += avVec.y;
			z += avVec.z;
			return *this;
		}

		inline cVector3<T>& operator-=(const cVector3<T>& avVec) const {
			x -= avVec.x;
			y -= avVec.y;
			z -= avVec.z;
			return *this;
		}

		inline cVector3<T>& operator*=(const cVector3<T> avVec) const {
			x *= avVec.x;
			y *= avVec.y;
			z *= avVec.z;
			return *this;
		}

		inline cVector3<T>& operator/=(const cVector3<T> avVec) const {
			x /= avVec.x;
			y /= avVec.y;
			z /= avVec.z;
			return *this;
		}

		inline cVector3<T>& operator+=(const T atX) const {
			x += atX;
			y += atX;
			z += atX;
			return *this;
		}

		inline cVector3<T>& operator-=(const T atX) const {
			x -= atX;
			y -= atX;
			z -= atX;
			return *this;
		}

		inline cVector3<T>& operator*=(const T atX) const {
			x *= atX;
			y *= atX;
			z *= atX;
			return *this;
		}

		inline cVector3<T>& operator/=(const T atX) const {
			x /= atX;
			y /= atX;
			z /= atX;
			return *this;
		}


		cVector3() : x(0), y(0), z(0) {}
		cVector3(T a) : x(a), y(a), z(a) {}
		cVector3(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
		cVector3(cVector3<T> const& avVec) : x(avVec.x), y(avVec.y), z(avVec.z) {}
		cVector3(cVector2<T> const& avVec) : x(avVec.x), y(avVec.y), z(0) {}

		T Length() const {
			return sqrt(x * x + y * y + z * z);
		}

		T LengthSqr() const {
			return (x * x + y * y + z * z);
		}

		T Normalize() {
			T Length = sqrt(x * x + y * y + z * z);
			T InvLength = 1 / Length;
			x *= InvLength;
			y *= InvLength;
			z *= InvLength;
			return Length;
		}
	};

	typedef cVector3<int> tVector3l;
	typedef cVector3<float> tVector3f;
}




#endif
