#include "graphics/Bitmap.h"

#include "resources/DevILBitmapLoaderHelper.h"

#include "system/Platform.h"

#include "engine/LogWriter.h"

#include <IL/il.h>
#include <cstdlib>

namespace alk {

	bool cDevILBitmapLoaderHelper::SaveBitmapDevIL(cBitmap* apBitmap, const twString& asFile)
	{
		FILE* pFile = cPlatform::OpenFile(asFile, L"wb");
		if (!pFile)
		{
			Error("Couldn't open file '%s' for writing!\n", cString::To8BitChar(asFile).c_str());
		}

		//ilSaveF();
		return false;
	}

	bool cDevILBitmapLoaderHelper::LoadBitmapDevIL(const twString& asFile)
	{
		// monster function call :o
		tString sExt = cString::To8BitChar(cString::ToLowerCaseW(cString::FileExtensionW(asFile)));

		Log("'%s'\n", sExt.c_str());

		ILint lFormat = GetILFormatFromExt(sExt);

		FILE* pFile = cPlatform::OpenFile(asFile, L"rb");

		if (pFile ==  NULL)
		{
			Error("Couldn't open file '%s' for reading!\n", cString::To8BitChar(asFile).c_str());
			return false;
		}

		int bRet = ilLoadF(lFormat, pFile);
		fclose(pFile);
		return (bool)bRet;
		
	}

	ILint cDevILBitmapLoaderHelper::GetILFormatFromExt(const tString& asExt)
	{
		if (asExt == "png") return IL_PNG;
		else if (asExt == "tga") return IL_TGA;
		else if (asExt == "jpg" || asExt == "jpeg") return IL_JPG;
		else if (asExt == "dds") return IL_DDS;
		else return -1;
	}

}