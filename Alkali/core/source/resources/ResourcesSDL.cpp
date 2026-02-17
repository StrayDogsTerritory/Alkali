#include "resources/ResourcesSDL.h"
#include "resources/SubLoader_BitmapDevIL.h"
#include "resources/cSubLoader_BitmapDevIL_DDS.h"
#include "resources/ResourceLoader.h"

#include "engine/LogWriter.h"

#include <cstdlib>
#include <IL/il.h>

namespace alk {

	cResourcesSDL::cResourcesSDL() : iResources()
	{
	
	}

	cResourcesSDL::~cResourcesSDL()
	{

	}

	static ILHANDLE ILAPIENTRY DevILOpen(const ILstring asFile)
	{
		return (ILHANDLE)fopen((char*)asFile, "wb");
	}

	static void ILAPIENTRY DevILClose(ILHANDLE apHandle)
	{
		fclose((FILE*)apHandle);
	}

	static int ILAPIENTRY DevILGetC(ILHANDLE apHandle)
	{
		return fgetc((FILE*)apHandle);
	}

	static int ILAPIENTRY DevILTell(ILHANDLE apHandle)
	{
		return ftell((FILE*)apHandle);
	}

	static int ILAPIENTRY DevILSeek(ILHANDLE apHandle, ILint alOffset, ILint alOrigin)
	{
		return fseek((FILE*)apHandle, (int)alOffset, (int)alOrigin);
	}

	static ILint ILAPIENTRY DevILRead(void* apBuffer,ILuint alSize,ILuint alElementCount, ILHANDLE apFile)
	{
		return (ILint)fread(apBuffer, (size_t)alSize, (size_t)alElementCount, (FILE*)apFile);
	}

	static ILboolean ILAPIENTRY DevILEoF(ILHANDLE apFile)
	{
		ILuint lOriPos, lFileSize;

		lOriPos = DevILTell(apFile);
		DevILSeek(apFile, 0, IL_SEEK_END);
		lFileSize = DevILTell(apFile);
		DevILSeek(apFile, lOriPos, IL_SEEK_SET);

		if (DevILTell(apFile) >= lFileSize)
			return IL_TRUE;
		else
			return IL_FALSE;
	}

	bool cResourcesSDL::Init()
	{
		// init DevIL
		Log("Initilizing DevIL\n");
		ilInit();

		Log("---DevIL Specifics---\n");
		Log("Vendor: %s\n", ilGetString(IL_VENDOR));
		Log("Version: %s\n",ilGetString(IL_VERSION_NUM));
		Log("Version Number: %d", ilGetInteger(IL_VERSION_NUM));
		Log("\n");

		ilSetRead(DevILOpen, DevILClose, DevILEoF, DevILGetC, DevILRead, DevILSeek, DevILTell);

		ilEnable(IL_ORIGIN_SET);
		ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);

		return true;
	}

	void cResourcesSDL::SetupBitmapLoader(iResourceLoader* apResourceLoader)
	{
		apResourceLoader->AddSubLoader(alkNew(cSubLoader_BitmapDevIL, ()));
		apResourceLoader->AddSubLoader(alkNew(cSubLoader_BitmapDevIL_DDS, ()));
	}

}