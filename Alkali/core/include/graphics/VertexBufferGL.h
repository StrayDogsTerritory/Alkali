#ifndef ALK_VERTEXBUFFERGL_H
#define ALK_VERTEXBUFFERGL_H

#include "graphics/VertexBuffer.h"
#include "GL/glew.h"

#include <vector>

namespace alk {

	static unsigned int GetGLTypeFromEnum(eVertexElementArrayFormat aType);
	static unsigned int GetGLFormatFromEnum(eVertexElementArrayFormat aFormat);
	static unsigned int GetGLDrawTypeFromEnum(eVertexBufferPrimitiveAssemblyType aDrawType);

	class cVertexBufferGL : public iVertexBuffer
	{
	public:
		cVertexBufferGL();
		~cVertexBufferGL();

		void Compile();
		void Draw();

		 void Bind();
		 void UnBind();

		 void Transform();
		 void CreateElementArray(eVertexElementArrayType aType, eVertexElementArrayFormat aFormat, unsigned int alElementNum);

		 void AddVertexColour(eVertexElementArrayType aType, cColour aCol);
		 void AddVertex(eVertexElementArrayType aType, tVector3f avVec);
		 void AddIndex(unsigned int alX);

	private:
		cVertexElementArray* GetArrayType(eVertexElementArrayType aType)
		{
			int lX = mvElementArrayIndex[aType];
			if (lX < 0)
				return NULL;
			return mvElementArray[lX];

		}

		GLuint mlBufferID;

		 std::vector<cVertexElementArray*> mvElementArray;
		 std::vector<unsigned int> mvIndexArray;
		char mvElementArrayIndex[eElementArrayType_LastEnum];
	};

}

#endif