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
		cTextureGL(const tString& asName, eTextureType aType, eTextureFilter aFilter, eTextureWrappingMode aMode);
		~cTextureGL();

		void GenerateTextureIDs(int alNumToGen);

		bool CreateTextureFromBitmap(cBitmap* apBitmap);
		bool CreateTextureFromRawData(tVector3l avDimensions, void* apData);
		bool CreateCubeMap();
		bool CreateAnimation();

		void Bind(int alUnit);

	private:
		GLenum EnumToGLPixelFormat(eBitmapFormat aFormat);
		GLenum EnumToGLTextureType(eTextureType aTextureType);
		GLenum EnumToGLTextureWrapMode(eTextureWrappingMode aTextureWrappingMode);
		GLenum EnumToGLTextureFilter(eTextureFilter aTextureFilter);


		bool CreateMipMaps();
		bool CreateTexture(int alID, cBitmapData* apBitmapData, int alNumberOfMipMaps,  tVector3l avSize, eBitmapFormat aFormat, bool abIsCompressed);

		bool CreateTextureFromBitmapIdx(cBitmap* apBitmap, int alIdx);
		bool CopyTextureDataToGL(eBitmapFormat Format, int alMipMapLevel,unsigned char* apData, size_t mlDataSize, tVector3l avSize, bool abIsCompressed);

		void SetupTextureProperties(int alIdx);



		bool mbUseMipMaps;

		eTextureFilter mFilter;
		eTextureWrappingMode mWrappingMode;
		eTextureType mTextureType;

		tString msName;
		tVector3l mvDimensions;
		size_t mlMemorySize;
		float mfAnisotropicFilteringDegree;

		std::vector<GLint> mvIDs;
	};


}

#endif
