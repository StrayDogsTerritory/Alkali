#ifndef ALK_XMLDOCUMENT_H
#define ALK_XMLDOCUMENT_H

#pragma warning(disable: 4996)
#include <list>
#include <map>

#include <stdio.h>

#include "system/String.h"

#include "graphics/Colour.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"

namespace alk {

	class iXmlNode;
	class iXmlElement;

	typedef std::list<iXmlNode*> tXmlNodeList;
	typedef tXmlNodeList::iterator tXmlNodeListIt;

	class iXmlNode
	{
	public:
		iXmlNode(const tString asVal, iXmlNode* apParent);
		virtual ~iXmlNode();

		const tString& GetVal() { return msVal; }
		void SetVal(const tString asVal) { msVal = asVal; }

		iXmlElement* ToElement();
		iXmlElement* GetFirstElement(const tString& asName);
		iXmlElement* GetFirstElement();
		iXmlElement* CreateChildElement(const tString& asName="");

		void AddChild(iXmlNode* apChild);
		void DestroyChild(iXmlNode* apChild);
		void DestroyAllChildren();

		iXmlNode* GetParent() { return mpParent; }
	private:
		iXmlNode* mpParent;
		tString msVal;

		tXmlNodeList mChildren;
	};

	typedef std::map<tString, tString> tXmlAttributeMap;
	typedef tXmlAttributeMap::iterator tXmlAttributeMapIt;

	class iXmlElement : public iXmlNode
	{
	public:
		iXmlElement(const tString& asName, iXmlNode* apParent);
		virtual ~iXmlElement();

		const char* GetAttribute(const tString& asString);
		tString GetAttributeString(const tString& asString, const tString& asFallback = "");
		int GetAttributeInt(const tString& asString, const int alFallback = 0);
		float GetAttributeFloat(const tString& asString, const float afFallback = 0.0f);
		bool GetAttributeBool(const tString& asString, const bool abFallback = false);
		tVector2f GetAttributeVector2f(const tString& asName, const tVector2f& aFallback = 0);
		tVector3f GetAttributeVector3f(const tString& asName, const tVector3f& aFallback = 0);
		tVector2l GetAttributeVector2l(const tString& asName, const tVector2l& aFallback = 0);
		tVector3l GetAttributeVector3l(const tString& asName, const tVector3l& aFallback = 0);
		cColour GetAttributeColour(const tString& asName, const cColour& aFallback = 0);

		void SetAttribute(const tString asName, const char* asValue);
		void SetAttributeString(const tString& asName, const tString& asValue);
		void SetAttributeInt(const tString& asName, const int alValue);
		void SetAttributeFloat(const tString& asName, const float afValue);
		void SetAttributeBool(const tString& asName, const bool abValue);
		void SetAttributeVector2f(const tString& asName, const tVector2f& avValue);
		void SetAttributeVector3f(const tString& asName, const tVector3f& avValue);
		void SetAttributeVector2l(const tString& asName, const tVector2l& avValue);
		void SetAttributeVector3l(const tString& asName, const tVector3l& avValue);
		void SetAttributeColour(const tString& asName, const cColour& acValue);

		tXmlAttributeMap* GetAttributeMap() { return &mAttributes; }
	private:
		tXmlAttributeMap mAttributes;
	};


	class iXmlDocument : public iXmlElement
	{
	public:
		iXmlDocument(const tString asName);
		virtual ~iXmlDocument() {}
		
		bool Load(const twString asPath);

		bool Save();
		bool SaveAs(const twString asPath);
	protected:
		void SaveErrorInfo(const tString& asReason, int alRow, int alCol) { msLastError = asReason; mlErrRow = alRow; mlErrCol = alCol; }
	private:
		virtual bool LoadFromFile(const twString asPath) = 0;
		virtual bool LoadFromString(const twString asData) = 0;

		virtual bool SaveToString(twString& asData) = 0;
		virtual bool SaveToFile(const twString asPath) = 0;
		
		/////////////
		// vars
		tString msPath;
		tString msLastError;
		int mlErrCol;
		int mlErrRow;
	};

}

#endif // XMLDOCUMENT_H
