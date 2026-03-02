#include "json/JsonDocument.h"

#include "system/MemoryManager.h"
#include "system/String.h"
#include "system/Platform.h"

#include "engine/LogWriter.h"

#include "json/cJson/cJSON.h"

namespace alk {
	cJsonNode::cJsonNode(const tString& asName)
	{
		msName = asName;
		msValue = "";
	}

	cJsonNode::~cJsonNode()
	{
		DeleteAll(mLstJsonNode);
	}

	void cJsonNode::AddNode(cJsonNode* apNode)
	{
		mLstJsonNode.push_back(apNode);
	}

	void cJsonNode::RemoveNode(const tString& asNode)
	{
		std::list<cJsonNode*>::iterator it = mLstJsonNode.begin();

		for (; it != mLstJsonNode.end(); ++it)
		{
			tString sName = (*it)->msName;
			if (sName == asNode)
			{
				mLstJsonNode.erase(it);
			}

		}
	}

	cJsonNode* cJsonNode::GetJsonNode(const tString& asName)
	{
		std::list<cJsonNode*>::iterator it = mLstJsonNode.begin();

		for (; it != mLstJsonNode.end(); ++it)
		{
			tString sName = (*it)->msName;
			if (sName == asName)
			{
				return *(it);
			}
		}

		return NULL;
	}


	iJsonDocument::iJsonDocument()
	{

	}

	iJsonDocument::~iJsonDocument() {}

	void iJsonDocument::Parse(const twString& asPath)
	{
		tString sJsonFile = "";
		FILE* pFile = cPlatform::OpenFile(asPath, L"rb");
		if (pFile)
		{
			fseek(pFile, 0, SEEK_END);
			size_t lSize = ftell(pFile);
			rewind(pFile);

			char* pBuffer = (char*)alkMalloc(sizeof(char) * lSize + 1);
			fread(pBuffer, sizeof(char), lSize, pFile);
			pBuffer[lSize] = 0; // null terminate the string

			sJsonFile = tString(pBuffer);
			//			Debug("File contents: '%s'\n", sJsonFile.c_str());
			cJSON* pJson = cJSON_Parse(pBuffer);

			cJSON* pJsonNested = pJson->child;

			cJSON* pJsonNestedNested = pJsonNested->child;

			cJSON* pJsonNestedNestedNested = pJsonNestedNested->next;
			Log("Dubug breakpoint stopper\n");
		}
	}
}

