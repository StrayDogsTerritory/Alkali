#include "graphics/Bitmap.h"

#include "resources/DevILBitmapLoaderHelper.h"

#include "system/Platform.h"

#include "engine/LogWriter.h"

#include <IL/il.h>
#include <cstdlib>

namespace alk {

	bool cDevILBitmapLoaderHelper::SaveBitmapDevIL(cBitmap* apBitmap, const twString& asFile)
	{
		FILE* pFile = cPlatform::OpenFile(asFile, L"wb"); // opens file
		if (!pFile) // if it's null
		{
			Error("Couldn't open file '%s' for writing!\n", cString::To8BitChar(asFile).c_str()); // let the user know
		}

		//ilSaveF();
		return false;
	}

	//-------------------------------------------------------------------------------------

	bool cDevILBitmapLoaderHelper::LoadBitmapDevIL(const twString& asFile)
	{
		// monster function call :o
		tString sExt = cString::To8BitChar(cString::ToLowerCaseW(cString::FileExtensionW(asFile))); // get the file extension, put it to lowercase and convert std::wstring to std::string

		//Log("'%s'\n", sExt.c_str());  //debug logging

		ILint lFormat = GetILFormatFromExt(sExt); // convert to format

		FILE* pFile = cPlatform::OpenFile(asFile, L"rb"); // open file

		if (pFile ==  NULL) // if file is null
		{
			Error("Couldn't open file '%s' for reading!\n", cString::To8BitChar(asFile).c_str()); // let the user know
			return false;
		}

		int bRet = ilLoadF(lFormat, pFile); // load the file in
		fclose(pFile); // close the file when we're done with it
		return (bool)bRet; // cast because return type of ilLoadF() is uint32... annoying
		
	}

	//-------------------------------------------------------------------------------------

	ILint cDevILBitmapLoaderHelper::GetILFormatFromExt(const tString& asExt)
	{
		// convert file names to IL enum, not going into specifics

		if (asExt == "png") return IL_PNG;
		else if (asExt == "tga") return IL_TGA;
		else if (asExt == "jpg" || asExt == "jpeg") return IL_JPG;
		else if (asExt == "dds") return IL_DDS;
		else return -1;
	}

	//-------------------------------------------------------------------------------------

}