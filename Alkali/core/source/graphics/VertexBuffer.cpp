#include "graphics/VertexBuffer.h"
#include "system/MemoryManager.h"

namespace alk {

	cVertexElementArray::cVertexElementArray(eVertexElementArrayFormat aFormat)
	{
		mlID = 0;

		mpFloatVec = NULL;
		mpIntVec   = NULL;
		mpByteVec  = NULL;

		switch(aFormat)
		{
			case eArrayFormat_Float: mpFloatVec = alkNew(tFloatVec); break;
			case eArrayFormat_Byte:  mpByteVec =  alkNew(tByteVec);  break;
			case eArrayFormat_Int:   mpIntVec =   alkNew(tIntVec);   break;
		}
	}

	cVertexElementArray::~cVertexElementArray()
	{
		switch (mFormat)
		{
		case eArrayFormat_Float: alkDelete(mpFloatVec); break;
		case eArrayFormat_Byte:  alkDelete(mpByteVec);  break;
		case eArrayFormat_Int:   alkDelete(mpIntVec);   break;
		}
	}

	size_t cVertexElementArray::Size()
	{ 
		switch (mFormat)
		{
			case eArrayFormat_Float: return mpFloatVec->size(); break;
			case eArrayFormat_Byte:  return mpByteVec->size(); break;
			case eArrayFormat_Int:   return mpIntVec->size(); break;
		}

		return 0;
	}

	void cVertexElementArray::Reserve(size_t alSize)
	{
		switch (mFormat)
		{
			case eArrayFormat_Float: mpFloatVec->reserve(alSize); break;
			case eArrayFormat_Byte:  mpByteVec->reserve(alSize); break;
			case eArrayFormat_Int:   mpIntVec->reserve(alSize); break;
		}
	}

	void cVertexElementArray::Resize(size_t alSize)
	{
		switch (mFormat)
		{
		case eArrayFormat_Float: mpFloatVec->resize((float)alSize);
		case eArrayFormat_Byte: mpFloatVec->resize((unsigned char)alSize);
		case eArrayFormat_Int: mpFloatVec->resize((int)alSize);
		}
	}

	void cVertexElementArray::PushBack(void* apData)
	{
		switch (mFormat)
		{
		case eArrayFormat_Float: mpFloatVec->push_back(*((const float*)apData)); break;
		case eArrayFormat_Byte:  mpByteVec->push_back(*((const unsigned char*)apData)); break;
		case eArrayFormat_Int:   mpIntVec->push_back(*((const int*)apData)); break;
		}
	}

	size_t cVertexElementArray::GetArrayStepSize()
	{
		switch (mFormat)
		{
		case eArrayFormat_Float: return sizeof(float);
		case eArrayFormat_Byte:  return sizeof(unsigned char);
		case eArrayFormat_Int:   return sizeof(int);
		}
		return 0;
	}

	void* cVertexElementArray::GetDataArray()
	{
		switch (mFormat)
		{
		case eArrayFormat_Float: { return &(*mpFloatVec)[0]; }
		case eArrayFormat_Byte:	{return &(*mpByteVec)[0]; }
		case eArrayFormat_Int: { return &(*mpIntVec)[0]; }
		}

		return NULL;
	}

}