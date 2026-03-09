#include "system/System.h"
#include "system/LogicTimer.h"
#include "system/MemoryManager.h"

#include "engine/LogWriter.h"

#include "json/JsonDocument.h"
#include "json/JsonDocumentCJSON.h"

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
		if (false)
		{
			Log("modified!\n");
			Warning("Application checksum is modified! If this hasn't been modified there is an error in the game files!\n");
		}
		else {
			Log("unmodified\n");
		}

		Log("---------------------------------------------\n");

		iJsonDocument* pJsonDoc = alkNew(cJsonDocumentCJSON, ());
		pJsonDoc->LoadDocument(L"TestJson.json");

		/*tString sVal = pJsonDoc->GetValueString("user_bindings", "fallback");
		int lVal = pJsonDoc->GetValueInt("scale",0);
		float fVal = pJsonDoc->GetValueFloat("volume.vca:/AMBIENT",0.0f);
		bool bVal = pJsonDoc->GetValueBool("ssao", false);

		Debug("Test String Val: '%s'\n", sVal.c_str());
		Debug("Test Int Val: '%d'\n", lVal);
		Debug("Test Float Val: '%f'\n", fVal);
		Debug("Test Bool Val: '%s'\n", bVal == true ? "true" : "false");*/

		alkDelete(pJsonDoc);

		return true;
	}

	void cSystem::OnUpdate(float afStep)
	{
		
	}

	int cSystem::GetChecksumTest()
	{
		FILE* pFile = cPlatform::OpenFile(L"Ozyonto.exe", L"rb");

		if (pFile == NULL)
		{
			Error("Couldn't Find Alkali.exe! Current working directory is '%s'\n", cString::To8BitChar(cPlatform::GetCurrentWorkingDirectory()).c_str());
			//	fclose(pFile);
			//FatalError("Couldn't find Ozyonto.exe!\n");
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