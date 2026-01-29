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
		float fAng = cMath::ToRad(360.0f);
		Log("'%g'\n", fAng);
		
		cQuaternion mqTest(kPI2, tVector3f(1, 0, 0));
		Log("'%s'\n", mqTest.ToString().c_str());
		//////////////////////
		// @TODO: Don't hardcode this
		Log("Engine Specifics:\n");
		Log("Version Number: %s.%s.%s \n", "0", "0", "0");
		Log("Build ID: %s \n", "20250930094205");
		Log("Checksum: %u... ", GetChecksumTest());
		if (false)
		{
			Log("modified!\n");
		}
		else
			Log("unmodified\n");
	

	}

	cSystem::~cSystem()
	{
	}

	void cSystem::OnUpdate(float afStep)
	{
		
	}

	int cSystem::GetChecksumTest()
	{
		FILE* pFile = cPlatform::OpenFile(L"Toronto.exe", L"rb");

		if (pFile == NULL)
		{
			//	fclose(pFile);
			FatalError("Couldn't find Toronto.exe!\n");
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

		Log("Checksum: '%s'\n", sTemp.c_str());

		int lHash = cString::Hash(sTemp);
		Log("Hash: '%u'\n", lHash);
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