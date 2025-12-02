#include "system/System.h"
#include "system/LogicTimer.h"
#include "system/MemoryManager.h"

#include "engine/LogWriter.h"

// remove this.
#include "system/Platform.h"
#include "system/Date.h"

#include "math/Math.h"
#include "math/Matrix.h"

namespace alk {

	cSystem::cSystem(iSystem* apSystemInterface) 
		: iUpdateable("System")
	{
		mpSystemInterface = apSystemInterface;
		mlUpdateTest = 0;

		size_t lSizeInt = sizeof(int);
		size_t lSizeLong = sizeof(long);
		size_t lSizeShort = sizeof(short);

		size_t lSizeFloat = sizeof(float);
		size_t lSizeDouble = sizeof(double);
		
		size_t lSizeChar = sizeof(char);
		size_t lSizeCharPtr = sizeof(char*);

		Log("Int: %d, Long: %d, Short: %d, Float: %d, Double: %d, Char: %d, Char*: %d\n", lSizeInt, lSizeLong, lSizeShort, lSizeFloat, lSizeDouble, lSizeChar, lSizeCharPtr);

		float fAngle = 45.0f;
		float fAngleRad = 0.785398f;
		Log("Angle Rad %g\n", cMath::ToRad(fAngle));
		Log("Angle Deg %g\n", cMath::ToDeg(fAngleRad));

		iJsonDocument Doc;
		Doc.Parse(L"");

		//////////////////////
		// @TODO: Don't hardcode this
	/*	Log("Engine Specifics:\n");
		Log("Version Number: %s.%s.%s \n", "0", "0", "0");
		Log("Build ID: %s \n", "20250930094205");
		Log("Checksum: %u... ", GetChecksumTest());
		if (false)
		{
			Log("modified\n");
		}
		else
			Log("unmodified\n");*/
	

	}

	cSystem::~cSystem()
	{
	}

	void cSystem::OnUpdate(float afStep)
	{
		Log("System Update is Running!\n");
		cDate Date = cPlatform::GetLocalTime();

		mlUpdateTest++;
		Log("System has updated: %d Times. Time: %s\n", mlUpdateTest, Date.ToStringTime().c_str());
		
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
		pBuffer[lSize] = '\0';
		fclose(pFile);

		tString sTemp = tString(pBuffer);

		int lHash = cString::Hash(sTemp);
		Log("Hash: '%u'\n", lHash);
		alkFree(pBuffer);
		return lHash;
	}

	cLogicTimer* cSystem::CreateLogicTimer(unsigned int alUpdatesPerSec)
	{
		return alkNew(cLogicTimer, (alUpdatesPerSec));
	}

}