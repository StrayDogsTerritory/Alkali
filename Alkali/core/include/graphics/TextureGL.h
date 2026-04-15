#ifndef ALK_TEXTUREGL_H
#define ALK_TEXTUREGL_H

#include "graphics/Bitmap.h"
#include "graphics/Texture.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Math.h"

#include <vector>

#include <GL/Glew.h>

/*
* Created by Simon Stroomer
*  OpenGL-specific implementation of textures. Derives from base class iTexure.
* Can create and destroy texure buffers on the GPU.
*/

namespace alk
{
	class cTextureGL : public iTexture
	{
	public:
		cTextureGL(const tString& asName, eTextureType aType, eTextureFilter aFilter, eTextureWrappingMode aMode); //constructor
		~cTextureGL(); //destructor

		void GenerateTextureIDs(int alNumToGen);//create OpenGL handles for each image in texure (though currently nothing can use more than 1 image)

		bool CreateTextureFromBitmap(cBitmap* apBitmap); //creates a texure from a bitmap formatted in-engine
		bool CreateTextureFromRawData(tVector3l avDimensions, void* apData); //UNUSED: creates a texture directly from raw bytes of data. Useful for framebuffers or other data needing to be interpreted as an image
		bool CreateCubeMap();//UNUSED: Creates a cubemap of 6 images
		bool CreateAnimation();//UNUSED: Creates a texture animation of n amount of images in series

		void Bind(int alUnit); // set this texture buffer as active to OpenGL

	private:
		GLenum EnumToGLPixelFormat(eBitmapFormat aFormat); // converts OpenGL format enums to Alkali enums
		GLenum EnumToGLTextureType(eTextureType aTextureType);// converts OpenGL texture type enums to Alkali enums
		GLenum EnumToGLTextureWrapMode(eTextureWrappingMode aTextureWrappingMode);// converts OpenGL texture wrapping mode enums to Alkali enums
		GLenum EnumToGLTextureFilter(eTextureFilter aTextureFilter);// converts OpenGL texture filter type enums to Alkali enums


		bool CreateMipMaps(); // UNUSED: creates mipmaps for texture automatically
		bool CreateTexture(int alID, cBitmapData* apBitmapData, int alNumberOfMipMaps,  tVector3l avSize, eBitmapFormat aFormat, bool abIsCompressed); //inherited abstract call to CreateTexutreIdx

		bool CreateTextureFromBitmapIdx(cBitmap* apBitmap, int alIdx);//inherited abstract call to CopyDataToGL()
		bool CopyTextureDataToGL(eBitmapFormat Format, int alMipMapLevel,unsigned char* apData, size_t mlDataSize, tVector3l avSize, bool abIsCompressed); //creates and adds image data into a memory buffer on the GPU

		void SetupTextureProperties(int alIdx); // adds specified texture data into the buffer



		bool mbUseMipMaps; //UNUSED: whether or not texture uses mipmaps

		eTextureFilter mFilter;//filter of texture
		eTextureWrappingMode mWrappingMode; //wrapping mode of texture
		eTextureType mTextureType; //type of texture

		tString msName; //texture's name
		tVector3l mvDimensions; // x y z coords of the texture
		size_t mlMemorySize; // size of texture in memory
		float mfAnisotropicFilteringDegree;//UNUSED: degree of anisotropic texture filtering

		std::vector<GLint> mvIDs; //array of ids the texture uses, important for currently unsupported cubemaps and animations
	};


}

#endif
