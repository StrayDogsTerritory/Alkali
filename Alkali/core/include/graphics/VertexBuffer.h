#ifndef ALK_VERTEXBUFFER_H
#define ALK_VERTEXBUFFER_H

#include "system/String.h"
#include "system/FlagBits.h"

#include "math/Math.h"
#include "graphics/Colour.h"

namespace alk {

	enum eVertexBufferDrawType
	{
		eDrawtype_Static,
		eDrawtype_Dynamic,
		eDrawtype_Stream,

		eDrawtype_LastEnum
	};

	enum eVertexBufferPrimitiveAssemblyType
	{
		ePrimitiveAssemblyType_Points,

		ePrimitiveAssemblyType_Lines,
		ePrimitiveAssemblyType_LineStrip,
		ePrimitiveAssemblyType_LineLoop,

		ePrimitiveAssemblyType_Tri,
		ePrimitiveAssemblyType_TriFan,
		ePrimitiveAssemblyType_TriStrip,

		ePrimitiveAssemblyType_LastEnum
	};

	enum eVertexElementArrayFormat
	{
		eArrayFormat_Float,
		eArrayFormat_Byte,
		eArrayFormat_Int,
		
		eArrayFormat_LastEnum
	};

	enum eVertexElementArrayType
	{
		eElementArrayType_Position,
		eElementArrayType_Normals,
		eElementArrayType_Colour,
		eElementArrayType_Tangent,

		// I don't know if this is needed...
		eElementArrayType_TriTangent,

		eElementArrayType_LastEnum
	};


	class cVertexElementArray
	{
	public:
		cVertexElementArray(eVertexElementArrayFormat aFormat);
		~cVertexElementArray();
		void Reserve(size_t alSize);
		void Resize(size_t alSize);
		void PushBack(void* apData);
		
		size_t GetArrayStepSize();

		size_t Size();

		void* GetDataArray();

		tByteVec* mpByteVec;
		tFloatVec* mpFloatVec;
		tIntVec* mpIntVec;

		eVertexElementArrayFormat mFormat;
		eVertexElementArrayType mType;

		unsigned int mlElementNum;

		unsigned int mlID;
	};

	class iVertexBuffer
	{
	public:
		iVertexBuffer(eVertexBufferDrawType aDrawType, eVertexBufferPrimitiveAssemblyType aPrimAssemblyType) {}
		virtual ~iVertexBuffer() {}

		virtual void Compile(eVertexBufferDrawType aDrawType = eDrawtype_LastEnum) =0;
		virtual void Draw(eVertexBufferPrimitiveAssemblyType aType = ePrimitiveAssemblyType_LastEnum)=0;
		virtual void Bind()=0;
		virtual void UnBind()=0;
	
		virtual void AddVertex(eVertexElementArrayType aType, tVector3f avVec)=0;
		virtual void AddVertexColour(eVertexElementArrayType aType, cColour aCol)=0;
		virtual void AddIndex(unsigned int alX)=0;

		virtual void Transform()=0;
		virtual void CreateElementArray(eVertexElementArrayType aType, eVertexElementArrayFormat aFormat, unsigned int alElementNum)=0;

	protected:
	};

}

#endif
