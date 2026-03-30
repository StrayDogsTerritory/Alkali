#ifndef ALK_MESH_H
#define ALK_MESH_H

#include "graphics/VertexBuffer.h"

#include "resources/ResourceBase.h"

#include "system/SystemTypes.h"

namespace alk {

	class cMesh : public iResourceBase
	{
	public:
		cMesh(const tString& asName, twString asFilePath);
		~cMesh();

		iVertexBuffer* GetVertexBuffer() { return mpVertexBuffer; }
		void SetVertexBuffer(iVertexBuffer* apVertexBuffer) { mpVertexBuffer = apVertexBuffer; }

		void CreateFromFile();

	private:
		twString msFilePath;
		tString msName;

		iVertexBuffer* mpVertexBuffer;
	};

}
#endif
