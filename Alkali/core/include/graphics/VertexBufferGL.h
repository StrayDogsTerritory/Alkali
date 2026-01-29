#ifndef ALK_VERTEXBUFFERGL_H
#define ALK_VERTEXBUFFERGL_H

#include "graphics/VertexBuffer.h"
#include "GL/glew.h"

#include <vector>

namespace alk {

	static unsigned int GetGLTypeFromEnum(eVertexElementArrayFormat aType);
	static unsigned int GetGLFormatFromEnum(eVertexElementArrayFormat aFormat);
	static unsigned int GetGLPrimitiveAssemblyTypeFromEnum(eVertexBufferPrimitiveAssemblyType aPrimAssemblyType);
	static unsigned int GetGLDrawTypeFromEnum(eVertexBufferDrawType aDrawType);

	class cVertexBufferGL : public iVertexBuffer
	{
	public:
		cVertexBufferGL();
		~cVertexBufferGL();

		void Compile(eVertexBufferDrawType aDrawType = eDrawtype_Static);
		void Draw(eVertexBufferPrimitiveAssemblyType aType);

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

		GLenum mDrawType;
		GLenum mPrimAssemblyType;

		GLuint mlBufferID;
		GLuint mlBufferArrayID;

		 std::vector<cVertexElementArray*> mvElementArray;
		 std::vector<unsigned int> mvIndexArray;
		char mvElementArrayIndex[eElementArrayType_LastEnum];
	};

}

#endif