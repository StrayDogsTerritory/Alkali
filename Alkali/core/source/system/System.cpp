#include "system/System.h"
#include "system/LogicTimer.h"
#include "system/MemoryManager.h"

#include "engine/LogWriter.h"

namespace alk {

	cSystem::cSystem(iSystem* apSystemInterface) 
		: iUpdateable("System")
	{
		mpSystemInterface = apSystemInterface;
	}

	cSystem::~cSystem()
	{
		Log("Quitting System module\n");
		Log("---------------------------------------------\n");
		Log("---------------------------------------------\n\n");
	}

	bool cSystem::Init()
	{
		Log("---------------------------------------------\n");
		//////////////////////
		// @TODO: Don't hardcode this
		Log("---Engine Specifics---\n");
		Log(" Version Number: %s.%s.%s \n", "0", "0", "0");
		Log(" Build ID: %s \n", "20250930094205");
		GetChecksumTest();
		Log("Status: ...");
		if (true)
		{
			Log("modified!\n");
			Warning("Application checksum is modified! If this hasn't been modified there is an error in the game files!\n");
		}
		else
			Log("unmodified!\n");


		Log("---------------------------------------------\n");
		return true;
	}

	void cSystem::OnUpdate(float afStep)
	{
		
	}

	int cSystem::GetChecksumTest()
	{
		FILE* pFile = cPlatform::OpenFile(L"Toronto.exe", L"rb");

		if (pFile == NULL)
		{
			Error("Couldn't Find Alkali.exe! Current working directory is '%s'\n", cString::To8BitChar(cPlatform::GetCurrentWorkingDirectory()).c_str());
			//	fclose(pFile);
			//FatalError("Couldn't find Toronto.exe!\n");
			//exit(1);
			return NULL;
		}
		fseek(pFile, 0, SEEK_END);
		size_t lSize = ftell(pFile);
		rewind(pFile);

		char* pBuffer = (char*)alkMalloc(sizeof(char) * lSize + 1);
		fread(pBuffer, sizeof(char), lSize, pFile);
		pBuffer[lSize] = 0;
		fclose(pFile);

		tString sTemp = tString(pBuffer);

		Log(" Checksum: '%s'\n", sTemp.c_str());

		int lHash = cString::Hash(sTemp);
		Log(" Hash: '%u'\n", lHash);
		alkFree(pBuffer);
		return lHash;
	}

	cLogicTimer* cSystem::CreateLogicTimer(unsigned int alUpdatesPerSec)
	{
		return alkNew(cLogicTimer, (alUpdatesPerSec));
	}

	

}