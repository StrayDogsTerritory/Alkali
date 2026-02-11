#ifndef ALK_TEXTUREGL_H
#define ALK_TEXTUREGL_H

#include "graphics/Bitmap.h"
#include "graphics/Texture.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Math.h"

#include <vector>

#include <GL/Glew.h>

namespace alk
{
	class cTextureGL : public iTexture
	{
	public:
		cTextureGL(const tString& asName);
		~cTextureGL();

		void GenerateTextureIDs(int alNumToGen);

		bool CreateTextureFromBitmap(tVector3l avDimensions,cBitmap* apBitmap);
		bool CreateTextureFromRawData(tVector3l avDimensions, void* apData);
		bool CreateCubeMap();
		bool CreateAnimation();

		

	private:
		GLint EnumToGLPixelFormat(eBitmapFormat aFormat);


		bool CreateMipMaps();
		void SetupGLFromBitmap(cBitmap* apBitmap);

		tString msName;
		tVector3l mvDimensions;
		size_t mlMemorySize;
		std::vector<GLint> mvIDs;
	};


}

#endif
