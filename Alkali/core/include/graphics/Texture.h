#ifndef ALK_TEXTURE_H
#define ALK_TEXTURE_H

#include "resources/ResourceBase.h"

namespace alk {

	enum eTextureWrappingMode
	{
		eTextureWrappingMode_Repeat,
		eTextureWrappingMode_Mirrored,
		eTextureWrappingMode_ClampToEdge,
		eTextureWrappingMode_ClampToBorder,

		eTextureWrappingMode_LastEnum,
	};

	enum eTextureFilter
	{
		eTextureFilter_Bilinear,
		eTextureFilter_Trilinear,
	};

	class cBitmap;

	class iTexture : public iResourceBase
	{
	public:
		iTexture(const tString& asName) : iResourceBase(asName, L"") {}
		virtual ~iTexture() {}

		// get to this later
		void Unload() {}
		bool Reload() { return false; }
		void Destroy() {}

		virtual	bool CreateTextureFromBitmap(tVector3l avDimensions, cBitmap* apBitmap)=0;
		 bool CreateTextureFromRawData(tVector3l avDimensions, void* apData);
		 bool CreateCubeMap();
		 bool CreateAnimation();

		

	protected:
	};

}

#endif
