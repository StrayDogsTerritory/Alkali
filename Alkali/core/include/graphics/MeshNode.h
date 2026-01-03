#ifndef ALK_MESHNODE_H
#define ALK_MESHNODE_H

#include "graphics/Mesh.h"

#include "Scene/Node.h"

namespace alk {

	class cMeshNode : public iNode
	{
	public:
		cMeshNode();
		~cMeshNode();

	private:
		cMesh* mpMesh;
	};
}

#endif