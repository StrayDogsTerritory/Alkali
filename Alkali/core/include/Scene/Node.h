#ifndef ALK_WORLD_NODE_H
#define ALK_WORLD_NODE_H

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

#include <map>

namespace alk {

	class cNode
	{
	public:
		cNode(cNode* apParent);
		~cNode();

		void CreateChild(cNode* apChildNode);
		void RemoveChild()

	protected:

		std::multimap<tString, cNode*> mChildMap;

		tMatrixf mMtxTransform;

		tVector3f mvLocalPos;
		tVector3f mvWorldPos;

		cQuaternion mqRot;
		tVector3f mvScale;
	};
}

#endif
