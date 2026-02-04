#ifndef ALK_TEXTUREGL_H
#define ALK_TEXTUREGL_H

#include "graphics/Texture.h"

#include <vector>

namespace alk
{
	class cTextureGL : public iTexture
	{
	public:
		cTextureGL();
		~cTextureGL();

		void GenerateTextureIDs(int alNumToGen);

		bool CreateTexture();
		bool CreateCubeMap();
		bool CreateAnimation();
	};

private:
	size_t mlMemorySize;
	std::vector<GLint> mvIDs;
}

#endif
