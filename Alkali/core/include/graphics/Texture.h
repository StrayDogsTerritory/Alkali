#ifndef ALK_TEXTURE_H
#define ALK_TEXTURE_H

#include "resources/ResourceBase.h"

/*
* Created by Simon Stroomer
* Base texture class for textures, inherits from resources
*/

namespace alk {

	/*
	* Some enums
	*/

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

	enum eTextureType
	{
		eTextureType_1D,
		eTextureType_2D,
		eTextureType_Rect,
		eTextureType_CubeMap,
		eTextureType_3D,

		eTextureType_LastEnum
	};


	class cBitmap; //forward declared bitmap class for function prototypes

	class iTexture : public iResourceBase
	{
	public:
		//-------------------------------------------------------------------------------------

		iTexture(const tString& asName) : iResourceBase(asName, L"") {} //constructor
		virtual ~iTexture() {} //destructor
		//-------------------------------------------------------------------------------------
		
		//-------------------------------------------------------------------------------------
		
		// get to this later
		void Unload() {} // UNUSED: unloads texture
		bool Reload() { return false; }// UNUSED: reloads texture
		void Destroy() {}// UNUSED: destroys texture

		//-------------------------------------------------------------------------------------

		virtual	bool CreateTextureFromBitmap( cBitmap* apBitmap)=0;

		//-------------------------------------------------------------------------------------

		 bool CreateTextureFromRawData(tVector3l avDimensions, void* apData);

		 //-------------------------------------------------------------------------------------
		
		 bool CreateCubeMap();

		 //-------------------------------------------------------------------------------------
		
		 bool CreateAnimation();

		 //-------------------------------------------------------------------------------------

		 virtual void Bind(int alUnit)=0;

		 //-------------------------------------------------------------------------------------
	protected:
	};

}

#endif
