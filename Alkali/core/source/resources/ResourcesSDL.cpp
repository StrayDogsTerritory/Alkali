#include "resources/ResourcesSDL.h"
#include "resources/SubLoader_BitmapDevIL.h"
#include "resources/cSubLoader_BitmapDevIL_DDS.h"
#include "resources/ResourceLoader.h"

#include "engine/LogWriter.h"

#include <cstdlib>
#include <IL/il.h>

namespace alk {

	//-------------------------------------------------------------------------------------

	cResourcesSDL::cResourcesSDL() : iResources()
	{
	
	}

	//-------------------------------------------------------------------------------------

	cResourcesSDL::~cResourcesSDL()
	{

	}


	/*
	* The following static functions are weird compatability things DeviL need to be able to load files, won't go into too much detail since there pretty standard STL functions
	*/

	//-------------------------------------------------------------------------------------

	static ILHANDLE ILAPIENTRY DevILOpen(const ILstring asFile)
	{
		return (ILHANDLE)fopen((char*)asFile, "wb"); // fopen
	}

	//-------------------------------------------------------------------------------------

	static void ILAPIENTRY DevILClose(ILHANDLE apHandle)
	{
		fclose((FILE*)apHandle); // fclose
	}

	//-------------------------------------------------------------------------------------

	static int ILAPIENTRY DevILGetC(ILHANDLE apHandle)
	{
		return fgetc((FILE*)apHandle); //getc
	}

	//-------------------------------------------------------------------------------------

	static int ILAPIENTRY DevILTell(ILHANDLE apHandle)
	{
		return ftell((FILE*)apHandle); //ftell
	}

	//-------------------------------------------------------------------------------------

	static int ILAPIENTRY DevILSeek(ILHANDLE apHandle, ILint alOffset, ILint alOrigin)
	{
		return fseek((FILE*)apHandle, (int)alOffset, (int)alOrigin); //fseek
	}

	//-------------------------------------------------------------------------------------

	static ILint ILAPIENTRY DevILRead(void* apBuffer,ILuint alSize,ILuint alElementCount, ILHANDLE apFile)
	{
		return (ILint)fread(apBuffer, (size_t)alSize, (size_t)alElementCount, (FILE*)apFile); //fread
	}

	//-------------------------------------------------------------------------------------

	static ILboolean ILAPIENTRY DevILEoF(ILHANDLE apFile)
	{
		ILuint lOriPos, lFileSize;

		lOriPos = DevILTell(apFile); // start at end of file
		DevILSeek(apFile, 0, IL_SEEK_END); // seek end of file
		lFileSize = DevILTell(apFile); // get the size of the file
		DevILSeek(apFile, lOriPos, IL_SEEK_SET); // move the file iterator to the origin at the end of file

		if (DevILTell(apFile) >= lFileSize) // if the file length is less or equal to the distrance of the file iterator at the end of the file, we've reached EoF
			return IL_TRUE;
		else // otherwise
			return IL_FALSE;
	}

	//-------------------------------------------------------------------------------------

	bool cResourcesSDL::Init()
	{
		// init DevIL
		Log("Initilizing DevIL\n"); // let the user know we're initializing
		ilInit(); // initialize DevIL

		Log("---DevIL Specifics---\n"); // log some more
		Log("Vendor: %s\n", ilGetString(IL_VENDOR)); // log the vendor
		Log("Version: %s\n",ilGetString(IL_VERSION_NUM)); // log the version number as a string
		Log("Version Number: %d", ilGetInteger(IL_VERSION_NUM)); // log version number as an integer
		Log("\n");

		ilSetRead(DevILOpen, DevILClose, DevILEoF, DevILGetC, DevILRead, DevILSeek, DevILTell); // let DevIL actually read things... this really shouldn't be necessary IMO but what ya gonna do?


		// probably not doing anything useful, but it was a common fix for some issues I was having where it wouldn't load
		ilEnable(IL_ORIGIN_SET); 
		ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);

		return true;
	}

	//-------------------------------------------------------------------------------------

	void cResourcesSDL::SetupBitmapLoader(iResourceLoader* apResourceLoader)
	{
		apResourceLoader->AddSubLoader(alkNew(cSubLoader_BitmapDevIL, ())); // add the sub loader for DevIL
		apResourceLoader->AddSubLoader(alkNew(cSubLoader_BitmapDevIL_DDS, ()));// add the sub loader for DevIL DDS
	}

	//-------------------------------------------------------------------------------------

}