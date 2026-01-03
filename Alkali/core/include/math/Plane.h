#ifndef ALK_PLANE_H
#define ALK_PLANE_H

template<class T>
class cPlane
{
public:
	union {
		struct {

			T a, b, c, d;
		};

		T v[4];
	};
};

typedef cPlane<float> tPlanef;
#endif
