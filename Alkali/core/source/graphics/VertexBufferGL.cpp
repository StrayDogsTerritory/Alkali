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

	static unsigned int GetGLPrimitiveAssemblyTypeFromEnum(eVertexBufferPrimitiveAssemblyType aPrimAssemblyType)
	{
		switch (aPrimAssemblyType)
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

	unsigned int GetGLDrawTypeFromEnum(eVertexBufferDrawType aDrawType)
	{
		switch (aDrawType)
		{
		case eDrawtype_Static: return GL_STATIC_DRAW;
		case eDrawtype_Dynamic: return GL_DYNAMIC_DRAW;
		case eDrawtype_Stream: return GL_STREAM_DRAW;
		}

		return 0;
	}

	cVertexBufferGL::cVertexBufferGL(eVertexBufferDrawType aDrawType, eVertexBufferPrimitiveAssemblyType aPrimAssemblyType) : iVertexBuffer(aDrawType,aPrimAssemblyType)
	{
		for (int i = 0; i < eElementArrayType_LastEnum; i++)
		{
			mvElementArrayIndex[i] = -1;
		}
		mlBufferID = 0;
		mlBufferArrayID = 0;

		mDrawType = aDrawType;
		mPrimAssemblyType = aPrimAssemblyType;
	
	}

	cVertexBufferGL::~cVertexBufferGL()
	{
		//glBindVertexArray(0);

		for (int i = 0; i < mvElementArray.size(); i++)
		{
			cVertexElementArray* pArr = mvElementArray[i];
			glDeleteBuffers(1, (GLuint*)&pArr->mlID);
		}

		glDeleteBuffers(1, (GLuint*)&mlBufferID);
		DeleteAll(mvElementArray);
		glDeleteVertexArrays(1, (GLuint*)&mlBufferArrayID);
		
	}


	void cVertexBufferGL::Compile(eVertexBufferDrawType aDrawType)
	{
		GLenum DrawType = GL_STATIC_DRAW;
		if (mDrawType == eDrawtype_Dynamic) DrawType = GL_DYNAMIC_DRAW;
		else if (mDrawType == eDrawtype_Stream) DrawType = GL_STREAM_DRAW;

		for (int i = 0; i < mvElementArray.size(); ++i)
		{
			cVertexElementArray* pArr = mvElementArray[i];

			GLenum Format = GetGLFormatFromEnum(pArr->mFormat);

			glGenBuffers(1, (GLuint*)&pArr->mlID);
			glBindBuffer(GL_ARRAY_BUFFER, pArr->mlID);
			// @TODO: Dont hard code this
			glBufferData(GL_ARRAY_BUFFER, pArr->Size() * pArr->GetArrayStepSize(), pArr->GetDataArray(), DrawType);
			//glEnableVertexAttribArray(i);
			//glVertexAttribPointer(i, pArr->mlElementNum, Format, GL_FALSE, 0, (void*)NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glGenBuffers(1, (GLuint*)&mlBufferID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mlBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int)mvIndexArray.size() * sizeof(unsigned int), &mvIndexArray[0], DrawType);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glGenVertexArrays(1, (GLuint*)&mlBufferArrayID);
	
		glBindVertexArray(0);
	}

	void cVertexBufferGL::Draw(eVertexBufferPrimitiveAssemblyType aType)
	{
		eVertexBufferPrimitiveAssemblyType PrimAsm = aType == ePrimitiveAssemblyType_LastEnum ? mPrimAssemblyType : aType;
		GLenum PrimMode = GetGLPrimitiveAssemblyTypeFromEnum(PrimAsm);

		glBindVertexArray(mlBufferArrayID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mlBufferID);

		glDrawElements(PrimMode, mvIndexArray.size(), GL_UNSIGNED_INT, (void*)NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
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

	//@TODO: Don't harcode this
	void cVertexBufferGL::Bind()
	{ 
		glBindVertexArray(mlBufferArrayID);


		for (int i = 0; i < mvElementArray.size(); ++i)
		{

			cVertexElementArray* pElem = mvElementArray[i];
			
			// check if we need to use glVertexAttribIPointer
			// ;@TODO: could optimize this in the future since the type will always be GL_FLOAT
			GLenum eFormat = GetGLFormatFromEnum(pElem->mFormat);

			glEnableVertexAttribArray(i);

			glBindBuffer(GL_ARRAY_BUFFER, pElem->mlID);
			glVertexAttribPointer(i, pElem->mlElementNum, eFormat, GL_FALSE, 0, (void*)NULL);
		}

		//for (int i = 0; i < mvElementArray.size(); ++i)
		//{

		//	cVertexElementArray* pElem = mvElementArray[i];

		//	// check if we need to use glVertexAttribIPointer
		//	if (pElem->mFormat != eArrayFormat_Int && pElem->mFormat != eArrayFormat_Byte) continue;

		//	GLenum eFormat = GetGLFormatFromEnum(pElem->mFormat);
		//	
		//	glEnableVertexAttribArray(i);

		//	glBindBuffer(GL_ARRAY_BUFFER, pElem->mlID);
		//	glVertexAttribIPointer(i, pElem->mlElementNum, eFormat, 0, (void*)NULL);
		//}

		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);

	}

	void cVertexBufferGL::UnBind()
	{
		glBindVertexArray(mlBufferArrayID);

		for (int i = 0; i < mvElementArray.size(); ++i)
		{

			cVertexElementArray* pElem = mvElementArray[i];

			GLenum eFormat = GetGLFormatFromEnum(pElem->mFormat);

//			glEnableVertexAttribArray(i);

			glBindBuffer(GL_ARRAY_BUFFER, pElem->mlID);
			glDisableVertexAttribArray(i);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
}