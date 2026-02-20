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


	cTextureManager::cTextureManager(cResources* apResources, cGraphics* apGraphics) 
		: iResourceManager(apResources->GetFileSearcher(), apGraphics->GetLowGraphics())
	{
		mpResources = apResources;
		mpGraphics = apGraphics;
	}

	cTextureManager::~cTextureManager()
	{
		DestroyAll();
	}

	iTexture* cTextureManager::Create2DTexture(const tString& asName)
	{
		twString sPath = cPlatform::GetFullFilePath(cString::ToWideChar(asName));

		iTexture* pTexture = static_cast<iTexture*> (FindResource(asName,sPath));

		if (pTexture == NULL && sPath != L"")
		{
			pTexture = mpiGraphics->CreateTexture(asName, eTextureType_2D, eTextureFilter_Trilinear, eTextureWrappingMode_Repeat);

			cBitmap* pBitmap = mpResources->GetBitmapLoader()->LoadBitmap(sPath);
			if (pBitmap == NULL) {
				Error("Texture Manager: Couldn't load bitmap '%s'!\n", cString::To8BitChar(sPath).c_str());
				return NULL;
			}

			// temp debugging
			bool bRet = pTexture->CreateTextureFromBitmap(pBitmap);

			int lDummy = 1;

			if (bRet == false)
			{
				Error("Texture Manager: Couldn't create texture '%s' from bitmap!\n", asName.c_str());
				alkDelete(pTexture);
				alkDelete(pBitmap);
				return NULL;
			}

			AddResource(pTexture);
			// delete the bitmap. It's not important.
			alkDelete(pBitmap);
		}
		if (pTexture)
		{
			pTexture->AddUser();
		}
		else Error("Couldn't load texture '%s'\n", asName.c_str());

		return pTexture;
	}

	void cTextureManager::Delete(iResourceBase* apResource)
	{
		apResource->RemoveUser();

		if (apResource->HasUsers() == false)
		{
			RemoveResource(apResource);
			alkDelete(apResource);
		}
	}

}