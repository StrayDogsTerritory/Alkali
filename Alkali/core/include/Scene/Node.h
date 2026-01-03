#ifndef ALK_WORLD_NODE_H
#define ALK_WORLD_NODE_H

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"

namespace alk {
	class iNode
	{
	public:
		iNode();
		virtual ~iNode();

	protected:
		tMatrixf mMtxTransform;

		tVector3f mvLocalPos;
		tVector3f mvWorldPos;

		tVector3f mvRot; //@TODO: make this a Quat when I implement it

		tVector3f mvScale;
	};
}

#endif
