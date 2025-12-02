#include "xml/XmlDocument.h"

#include "system/SystemTypes.h"

namespace alk {

	iXmlNode::iXmlNode(const tString asVal, iXmlNode* apParent)
	{
		msVal = asVal;
		mpParent = apParent;
	}

	iXmlElement* iXmlNode::GetFirstElement()
	{
		if (mChildren.empty()) return NULL;

		tXmlNodeListIt it = mChildren.begin();
		iXmlNode *pNode = *it;

		return static_cast<iXmlElement*>(pNode);
	}

	iXmlElement* iXmlNode::CreateChildElement(const tString& asName)
	{ 
		iXmlElement* pElem = alkNew(iXmlElement, (asName, this));
		AddChild(pElem);
		return pElem;
	}

	void iXmlNode::AddChild(iXmlNode* apNode)
	{ 
		mChildren.push_back(apNode);
	}

	void iXmlNode::DestroyChild(iXmlNode* apChild)
	{
		FindAndDelete(mChildren, apChild);
	}

	iXmlNode::~iXmlNode()
	{
		DestroyAllChildren();
	}

	iXmlElement* iXmlNode::ToElement()
	{
		return static_cast<iXmlElement*> (this);
	}

	void iXmlNode::DestroyAllChildren()
	{
		DeleteAll(mChildren);
	}





	iXmlElement::iXmlElement(const tString& asName, iXmlNode* apParent) : iXmlNode(asName, apParent)
	{
	}

	iXmlElement::~iXmlElement()
	{
	}

	const char* iXmlElement::GetAttribute(const tString& asName)
	{
		tXmlAttributeMapIt it = mAttributes.find(asName);
		if (it != mAttributes.end())
		{
			return it->second.c_str();
		}
		return NULL;
	}

	tString iXmlElement::GetAttributeString(const tString& asString,const tString& asFallback)
	{
		const char* pString = GetAttribute(asString);
		return cString::toString(pString, asFallback);
	}

	int iXmlElement::GetAttributeInt(const tString& asString, const int alFallback)
	{
		const char* pString = GetAttribute(asString);
		return cString::ToInt(pString, alFallback);
	}

	float iXmlElement::GetAttributeFloat(const tString& asString, const float afFallback)
	{
		const char* pString = GetAttribute(asString);
		return cString::ToFloat(pString, afFallback);
	}

	bool iXmlElement::GetAttributeBool(const tString& asString, const bool abFallback)
	{
		const char* pString = GetAttribute(asString);
		return cString::ToFloat(pString, abFallback);
	}

	static char sTempBuff[1024];
	void iXmlElement::SetAttribute(const tString asName, const char* asValue)
	{
		tXmlAttributeMapIt it = mAttributes.find(asName);

		if (it != mAttributes.end())
		{
			it->second = asValue;
		}
		else
		{
			mAttributes.insert(tXmlAttributeMap::value_type(asName, asValue));
		}
	}

	void iXmlElement::SetAttributeString(const tString& asName, const tString& asValue)
	{
		sprintf(sTempBuff, "%s", asValue.c_str());
		SetAttribute(asName,sTempBuff);
	}

	void iXmlElement::SetAttributeInt(const tString& asName, const int alValue)
	{
		sprintf(sTempBuff, "%d", alValue);
		SetAttribute(asName, sTempBuff);
	}

	void iXmlElement::SetAttributeFloat(const tString& asName, const float afValue)
	{
		sprintf(sTempBuff, "%g", afValue);
		SetAttribute(asName, sTempBuff);

	}

	void iXmlElement::SetAttributeBool(const tString& asName, const bool abValue)
	{
		SetAttribute(asName, abValue ? "true" : "false");
	}

}