#include "graphics/VertexBufferGL.h"

#include "engine/LogWriter.h"

#include "GL/glew.h"

namespace alk {

	static unsigned int GetGLTypeFromEnum(eVertexElementArrayType aType)
	{
		switch (aType)
		{
		case eElementArrayType_Position: return GL_VERTEX_ARRAY;
		case eElementArrayType_Normals: return GL_NORMAL_ARRAY;
		case eElementArrayType_Colour: return GL_COLOR_ARRAY;
		}

		return 0;
	}

	static unsigned int GetGLFormatFromEnum(eVertexElementArrayFormat aFormat)
	{
		switch (aFormat)
		{
		case eArrayFormat_Float: return GL_FLOAT;
		case eArrayFormat_Byte: return GL_UNSIGNED_BYTE;
		case eArrayFormat_Int: return GL_INT;
		}

		return 0;
	}

	static unsigned int GetGLDrawTypeFromEnum(eVertexBufferPrimitiveAssemblyType aDrawType)
	{
		switch (aDrawType)
		{
		case ePrimitiveAssemblyType_Tri: return GL_TRIANGLES;
		case ePrimitiveAssemblyType_TriFan: return GL_TRIANGLE_FAN;
		case ePrimitiveAssemblyType_TriStrip: return GL_TRIANGLE_STRIP;

		case ePrimitiveAssemblyType_Lines: return GL_LINES;
		case ePrimitiveAssemblyType_LineStrip: return GL_LINE_STRIP;
		case ePrimitiveAssemblyType_LineLoop: return GL_LINE_LOOP;

		case ePrimitiveAssemblyType_Points: return GL_POINTS;
		}

		return 0;
	}

	cVertexBufferGL::cVertexBufferGL()
	{
		for (int i = 0; i < eElementArrayType_LastEnum; i++)
		{
			mvElementArrayIndex[i] = -1;
		}
		mlBufferID = 0;

		// test to see if it stops crashing
	//	mvIndexArray.reserve(50);
	}

	cVertexBufferGL::~cVertexBufferGL()
	{
		for (int i = 0; i < mvElementArray.size(); i++)
		{
			cVertexElementArray* pArr = mvElementArray[i];
			glDeleteBuffers(1, (GLuint*)&pArr->mlID);
		}

		glDeleteBuffers(1, (GLuint*)&mlBufferID);

		DeleteAll(mvElementArray);
	}


	void cVertexBufferGL::Compile()
	{

		for (int i = 0; i < mvElementArray.size(); i++)
		{
			cVertexElementArray* pArr = mvElementArray[i];

			glGenBuffers(1, (GLuint*)&pArr->mlID);
			glBindBuffer(GL_ARRAY_BUFFER, pArr->mlID);
			// @TODO: Dont hard code this
			glBufferData(GL_ARRAY_BUFFER, pArr->Size() * sizeof(float), pArr->GetDataArray(), GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glGenBuffers(1, (GLuint*)&mlBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mlBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int)mvIndexArray.size() * sizeof(unsigned int), &mvIndexArray[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void cVertexBufferGL::Draw()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mlBufferID);

		glDrawElements(GL_TRIANGLES, mvIndexArray.size(), GL_UNSIGNED_INT, (char*)NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void cVertexBufferGL::Transform()
	{
		// fill this later
	}

	void cVertexBufferGL::CreateElementArray(eVertexElementArrayType aType, eVertexElementArrayFormat aFormat, unsigned int alElementNum)
	{
		cVertexElementArray* pArray = alkNew(cVertexElementArray, (aFormat));
	
		pArray->mFormat = aFormat;
		pArray->mType = aType;
		pArray->mlElementNum = alElementNum;

		mvElementArrayIndex[aType] = (char)mvElementArray.size();
		mvElementArray.push_back(pArray);
	}

	void cVertexBufferGL::AddVertex(eVertexElementArrayType aType, tVector3f avVec)
	{
		cVertexElementArray* pElem = GetArrayType(aType);
		pElem->PushBack(&avVec.x);
		pElem->PushBack(&avVec.y);

		if (pElem->mlElementNum > 2)
			pElem->PushBack(&avVec.z);

		if (pElem->mlElementNum > 3)
		{
			float fX = 1;
			pElem->PushBack(&fX);
		}
	}

	void cVertexBufferGL::AddVertexColour(eVertexElementArrayType aType, cColour aCol)
	{
							// I give up naming these
		cVertexElementArray* pElem = GetArrayType(aType);
		
		if (pElem->mFormat == eArrayFormat_Float) 
		{
			pElem->PushBack(&aCol.r);
			pElem->PushBack(&aCol.g);
			pElem->PushBack(&aCol.b);
			pElem->PushBack(&aCol.a);
		}
	}

	void cVertexBufferGL::AddIndex(unsigned int alX)
	{
		mvIndexArray.push_back(alX);
	}

	void cVertexBufferGL::Bind()
	{ 
		for (int i = 0; i < mvElementArray.size(); ++i)
		{
			cVertexElementArray* pElem = mvElementArray[i];
			if (pElem->mType == eElementArrayType_Position) continue;

			GLenum mFormat = GetGLFormatFromEnum(pElem->mFormat);

			glEnableClientState(GetGLTypeFromEnum(pElem->mType));

			glBindBuffer(GL_ARRAY_BUFFER, pElem->mlID);

			switch (pElem->mType)
			{
			case eElementArrayType_Normals:
				glNormalPointer(mFormat, 0, (char*)NULL);
				break;

			case eElementArrayType_Colour:
				glColorPointer(pElem->mlElementNum, mFormat, 0, (char*)NULL);
				break;

			}
		}

		for (int i = 0; i < mvElementArray.size(); ++i)
		{
			cVertexElementArray* pElem = mvElementArray[i];
			if (pElem->mType != eElementArrayType_Position) continue;

			GLenum mFormat = GetGLFormatFromEnum(pElem->mFormat);

			glEnableClientState(GetGLTypeFromEnum(pElem->mType));

			glBindBuffer(GL_ARRAY_BUFFER, pElem->mlID);
			glVertexPointer(pElem->mlElementNum, mFormat, 0, (char*)NULL);
			
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void cVertexBufferGL::UnBind()
	{

	}
	
}