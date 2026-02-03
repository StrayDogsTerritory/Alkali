#ifndef ALK_TEXTUREGL_H
#define ALK_TEXTUREGL_H

#include "graphics/Texture.h"

namespace alk
{
	class cTextureGL : public iTexture
	{
	public:
		cTextureGL();
		~cTextureGL();

		bool CreateTexture();
	};

}

#endif
