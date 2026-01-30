#include "system/System.h"
#include "system/LogicTimer.h"
#include "system/MemoryManager.h"

#include "engine/LogWriter.h"

// remove this.
#include "system/Platform.h"
#include "system/Date.h"

#include "math/Math.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

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
		// @TODO: maybe don't do this? Decide later!
		Log("---Logical Hardware Specifics---\n");
		Log("-Processor Specifics-\n");
		Log("Processor Model: %s\n", "");
		Log("Processor Architecture: %s\n", "");
		Log("Processor Physical Cores: %d\n", -1);
		Log("Processor Logical processors: %d\n", -1);
		Log("-RAM Specifics-\n");
		Log("Total Physical RAM: %u Bytes\n", cPlatform::GetTotalRam());
		Log("Available Physical RAM: %u Bytes\n",cPlatform::GetAvailableRam());

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
			Error("Couldn't Find Alkali.exe! Current workin directory is '%s'\n", cString::To8BitChar(cPlatform::GetCurrentWorkingDirectory()).c_str());
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

	void cSystem::TestString()
	{
		Error("I SHITTED MYSELF!!!!!\n");
	}

}