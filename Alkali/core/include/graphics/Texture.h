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

	class iTexture : public iResourceBase
	{
	public:
		iTexture();
		virtual ~iTexture() {}

		bool CreateCubemap();
		bool CreateTexture();

	protected:
	};

}

#endif
