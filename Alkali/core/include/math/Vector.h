#ifndef ALK_VECTOR_H
#define ALK_VECTOR_H

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
		
			T InvLength = 1/sqrt(x * x + y * y);
			x *= InvLength;
			y *= InvLength;
		}
	};



	template<class T>
	class cVector3
	{
		union {
			struct {
				T x, y, z;
			};
			T v[3];
		};

	};
}

#endif 
