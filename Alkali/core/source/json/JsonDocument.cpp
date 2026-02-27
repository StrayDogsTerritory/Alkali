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

	void iJsonDocument::Parse(const twString& asPath)
	{
		tString sTest  = "{\"user\": \"Jack\", \"age\": 27}";
	


	}
}

