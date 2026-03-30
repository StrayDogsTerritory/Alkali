#ifndef ALK_VECTOR2_H
#define ALK_VECTOR2_H

#include <Math.h>
//#include <stdio.h>
#include "system/SystemTypes.h"

typedef std::string tTest_t;

namespace alk {

	template<class T>
	class cVector2
	{
	public:
		union {
			struct {
				T x, y;
			};
			T v[2];
		};

		inline cVector2<T>& operator=(const cVector2<T>& avVec) {
			x = avVec.x; y = avVec.y; 
			return *this; 
		}

		inline cVector2<T>& operator=(const T atX) {
			x = atX; y = atX;
			return *this;
		}

		inline bool operator==(const cVector2<T>& avVec)  {
			if (x == avVec.x && y == avVec.y) return true;
			else return false;
		}

		inline bool operator!=(const cVector2<T>& avVec) {
			if (x == avVec.x && y == avVec.y) return false;
			else return true;
		}
		
		inline cVector2<T>& operator+(const cVector2<T>& avVec) {
			cVector2<T> vVec;
			vVec.x = x + avVec.x;
			vVec.y = y + avVec.y;
			return vVec;
		}

		inline cVector2<T>& operator-(const cVector2<T>& avVec) {
			cVector2<T> vVec;
			vVec.x = x - avVec.x;
			vVec.y = y - avVec.y;
			return vVec;
		}

		inline cVector2<T>& operator*(const cVector2<T> avVec) {
			cVector2<T> vVec;
			vVec.x = x * avVec.x;
			vVec.y = y * avVec.y;
			return vVec;
		}

		inline cVector2<T>& operator/(const cVector2<T> avVec) {
			cVector2<T> vVec;
			vVec.x = x / avVec.x;
			vVec.y = y / avVec.y;
			return vVec;
		}

		inline cVector2<T>& operator+(const T atX) {
			cVector2<T> vVec;
			vVec.x = x + atX;
			vVec.y = y + atX;
			return vVec;
		}

		inline cVector2<T>& operator-(const T atX) {
			cVector2<T> vVec;
			vVec.x = x - atX;
			vVec.y = y - atX;
			return vVec;
		}

		inline cVector2<T>& operator*(const T atX) {
			cVector2<T> vVec;
			vVec.x = x * atX;
			vVec.y = y * atX;
			return vVec;
		}

		inline cVector2<T>& operator/(const T atX) {
			cVector2<T> vVec;
			vVec.x = x / atX;
			vVec.y = y / atX;
			return vVec;
		}

		inline cVector2<T>& operator+=(const cVector2<T>& avVec){
			x += avVec.x;
			y += avVec.y;
			return *this;
		}

		inline cVector2<T>& operator-=(const cVector2<T>& avVec){
			x -= avVec.x;
			y -= avVec.y;
			return *this;
		}

		inline cVector2<T>& operator*=(const cVector2<T> avVec){
			x *= avVec.x;
			y *= avVec.y;
			return *this;
		}

		inline cVector2<T>& operator/=(const cVector2<T> avVec){
			x /= avVec.x;
			y /= avVec.y;
			return *this;
		}

		inline cVector2<T>& operator+=(const T atX){
			x += atX;
			y += atX;
			return *this;
		}

		inline cVector2<T>& operator-=(const T atX) {
			x -= atX;
			y -= atX;
			return *this;
		}

		inline cVector2<T>& operator*=(const T atX) {
			x *= atX;
			y *= atX;
			return *this;
		}

		inline cVector2<T>& operator/=(const T atX) {
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

		tString ToString()
		{
			char Buf[256];
			sprintf(Buf, "[%g, %g]", (float)x, (float)y);
			return tString(Buf);
		}

		tString ToFileString()
		{
			char buf[256];
			sprintf(buf, "%g %g", x, y);
			return tString(buf);
		}
	};

	typedef cVector2<int> tVector2l;
	typedef cVector2<float> tVector2f;

}

#endif 
