#ifndef ALK_VECTOR2_H
#define ALK_VECTOR2_H

#include <Math.h>

namespace alk {

	template<class T>
	class cVector2
	{
	public:
		union {
			struct {
				T x, y;
			};
			T a[2];
		};

		inline cVector2<T>& operator=(const cVector2<T>& avVec) {
			x = avVec.x; y = avVec.y; 
			return *this; 
		}

		inline cVector2<T>& operator=(const T atX) {
			x = atX; y = atX;
			return *this;
		}

		inline cVector2<T>& operator==(const cVector2<T>& avVec) const {
			if (x == avVec.x && y == avVec.y) return true;
			else return false;
		}

		inline cVector2<T>& operator!=(const cVector2<T>& avVec) const {
			if (x == avVec.x && y == avVec.y) return false;
			else return true;
		}
		
		inline cVector2<T>& operator+(const cVector2<T>& avVec) const {
			cVector2<T> vVec;
			vVec.x = x + avVec.x;
			vVec.y = y + avVec.y;
			return vVec;
		}

		inline cVector2<T>& operator-(const cVector2<T>& avVec) const {
			cVector2<T> vVec;
			vVec.x = x - avVec.x;
			vVec.y = y - avVec.y;
			return vVec;
		}

		inline cVector2<T>& operator*(const cVector2<T> avVec) const {
			cVector2<T> vVec;
			vVec.x = x * avVec.x;
			vVec.y = y * avVec.y;
			return vVec;
		}

		inline cVector2<T>& operator/(const cVector2<T> avVec) const {
			cVector2<T> vVec;
			vVec.x = x / avVec.x;
			vVec.y = y / avVec.y;
			return vVec;
		}

		inline cVector2<T>& operator+(const T atX) const {
			cVector2<T> vVec;
			vVec.x = x + atX;
			vVec.y = y + atX;
			return vVec;
		}

		inline cVector2<T>& operator-(const T atX) const {
			cVector2<T> vVec;
			vVec.x = x - atX;
			vVec.y = y - atX;
			return vVec;
		}

		inline cVector2<T>& operator*(const T atX) const {
			cVector2<T> vVec;
			vVec.x = x * atX;
			vVec.y = y * atX;
			return vVec;
		}

		inline cVector2<T>& operator/(const T atX) const {
			cVector2<T> vVec;
			vVec.x = x / atX;
			vVec.y = y / atX;
			return vVec;
		}

		inline cVector2<T>& operator+=(const cVector2<T>& avVec) const{
			x += avVec.x;
			y += avVec.y;
			return *this;
		}

		inline cVector2<T>& operator-=(const cVector2<T>& avVec) const{
			x -= avVec.x;
			y -= avVec.y;
			return *this;
		}

		inline cVector2<T>& operator*=(const cVector2<T> avVec) const{
			x *= avVec.x;
			y *= avVec.y;
			return *this;
		}

		inline cVector2<T>& operator/=(const cVector2<T> avVec) const{
			x /= avVec.x;
			y /= avVec.y;
			return *this;
		}

		inline cVector2<T>& operator+=(const T atX) const{
			x += atX;
			y += atX;
			return *this;
		}

		inline cVector2<T>& operator-=(const T atX) const{
			x -= atX;
			y -= atX;
			return *this;
		}

		inline cVector2<T>& operator*=(const T atX) const{
			x *= atX;
			y *= atX;
			return *this;
		}

		inline cVector2<T>& operator/=(const T atX) const{
			x /= atX;
			y /= atX;
			return *this;
		}


		cVector2() : x(0), y(0) {}
		cVector2(T a) : x(a), y(a) {}
		cVector2(T ax, T ay) : x(ax), y(ay) {}
		cVector2(const cVector2& avVec) : x(avVec.x), y(avVec.y) {}

		T Length() const {
			return sqrt(x * x + y * y);
		}

		T LengthSqr() const {
			return (x * x + y * y);
		}

		T Normalize() {
			T Length = sqrt(x * x + y * y);
			T InvLength = 1/Length;
			x *= InvLength;
			y *= InvLength;

			return Length;
		}
	};

	typedef cVector2<int> tVector2l;
	typedef cVector2<float> tVector2f;

}

#endif 
