#include "resources/TextureManager.h"
#include "resources/Resources.h"
#include "resources/BitmapLoader.h"

#include "graphics/Graphics.h"
#include "graphics/GraphicsInterface.h"
#include "graphics/Texture.h"
#include "graphics/Bitmap.h"

#include "system/Platform.h"

#include "engine/LogWriter.h"

namespace alk {

	//-------------------------------------------------------------------------------------

	cTextureManager::cTextureManager(cResources* apResources, cGraphics* apGraphics) 
		: iResourceManager(apResources->GetFileSearcher(), apGraphics->GetLowGraphics())
	{
		mpResources = apResources; //points to the central resource module
		mpGraphics  = apGraphics;  //points to the cental graphics module
	}

	//-------------------------------------------------------------------------------------

	cTextureManager::~cTextureManager()
	{
		DestroyAll(); //delete every mananged texture
	}

	//-------------------------------------------------------------------------------------

	iTexture* cTextureManager::Create2DTexture(const tString& asName)
	{
		twString sPath = cPlatform::GetFullFilePath(cString::ToWideChar(asName)); //get the file path of the texture from the name

		iTexture* pTexture = static_cast<iTexture*> (FindResource(asName,sPath)); //cast the base class into the API-specific class

		if (pTexture == NULL && sPath != L"") //if there is no texture currently managed with the same path as the one we're creating
		{
			pTexture = mpiGraphics->CreateTexture(asName, eTextureType_2D, eTextureFilter_Trilinear, eTextureWrappingMode_Repeat); // creates a texture with these params

			cBitmap* pBitmap = mpResources->GetBitmapLoader()->LoadBitmap(sPath); // load the bitmap with the file path of our texture (always the same)
			if (pBitmap == NULL) {
				Error("Texture Manager: Couldn't load bitmap '%s'!\n", cString::To8BitChar(sPath).c_str()); // let the user know the bitmap can't be loaded
				return NULL; //return NULL
			}

			// temp debugging // not anymore
			bool bRet = pTexture->CreateTextureFromBitmap(pBitmap); // create the texture from the bitmap

			int lDummy = 1; // temp

			if (bRet == false) // if the bitmap could not be loaded
			{
				Error("Texture Manager: Couldn't create texture '%s' from bitmap!\n", asName.c_str());// let the user know the bitmap can't be loaded
				alkDelete(pTexture); // delete the NULL texture
				alkDelete(pBitmap); // delete the bitmap
				return NULL; 
			}

			AddResource(pTexture); // add the texture as a resource
			// delete the bitmap. It's not important.
			alkDelete(pBitmap);
		}
		if (pTexture)
		{
			pTexture->AddUser(); // the manager takes control of the texture now
		}
		else Error("Couldn't load texture '%s'\n", asName.c_str()); // if there's an error, tell the user

		return pTexture;
	}

	//-------------------------------------------------------------------------------------

	void cTextureManager::Delete(iResourceBase* apResource)
	{
		apResource->RemoveUser(); //remove the resource as a user

		if (apResource->HasUsers() == false) //if there are no users
		{
			RemoveResource(apResource); //remove the resource from the manager
			alkDelete(apResource); //delete the resource
		}
	}

	//-------------------------------------------------------------------------------------
}