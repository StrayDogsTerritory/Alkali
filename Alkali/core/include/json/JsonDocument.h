#ifndef ALK_JSONDOCUMENT_H
#define ALK_JSONDOCUMENT_H

#include "system/SystemTypes.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

#include <map>
#include <list>

namespace alk {



	enum eJsonObjectType
	{
		eJsonObjectType_Object,
		eJsonObjectType_Array,
		eJsonObjectType_LastEnum
	};


	typedef std::multimap<tString, tString> tMapValues;
	typedef tMapValues::iterator tMapValIterator;


	class cJsonObject
	{
	public:
		cJsonObject(const tString& asName) : mpParent(NULL), msName(asName){}
		~cJsonObject();


		cJsonObject* GetChildObject(const tString& asName);

		cJsonObject* CreateChildObject(const tString& asName);
		void DestroyChildObject(const tString& asName);
		

		void SetValue(const tString& asName, const tString asVal);

		void SetValueString(const tString& asName, const tString& asValue, const tString& asFallBack = "");
		void SetValueInt(const tString& asName, int alX, const tString& asFallBack = "");
		void SetValueFloat(const tString& asName, float afX, const tString& asFallBack = "");
		void SetValueBool(const tString& asName, bool abX, const tString& asFallBack = "");
		void SetValueVector2l(const tString& asName, tVector2l avVec, const tString& asFallback = "");
		void SetValueVector2f(const tString& asName, tVector2f avVec, const tString& asFallback = "");
		void SetValueVector3l(const tString& asName, tVector3l avVec, const tString& asFallback = "");
		void SetValueVector3f(const tString& asName, tVector3f avVec, const tString& asFallback = "");

		tString GetValue(const tString& asName);

		tString GetValueString(const tString& asName, const char* asFallback = "");
		int GetValueInt(const tString& asName, int alFallback=0);
		float GetValueFloat(const tString& asName, float afFallback=0.0f);
		bool GetValueBool(const tString& asName, bool abFallback = false);
		tVector2l GetValueVector2l(const tString& asName, tVector2l avFallback = 0);
		tVector2f GetValueVector2f(const tString& asName, tVector2f avFallback = 0);
		tVector3l GetValueVector3l(const tString& asName, tVector3l avFallback = 0);
		tVector3f GetValueVector3f(const tString& asName, tVector3f avFallback = 0);

		tString msName;

		cJsonObject* mpParent;

		std::list<cJsonObject*> mLstChildren;

		tMapValues mMapValues;
	
	private:
		void AddChild(cJsonObject* apObject);
	};

	
	class iJsonDocument : public cJsonObject
	{
	public:
		iJsonDocument(const tString& asName);
		~iJsonDocument();

		bool LoadDocument(const twString& asFilePath);
		bool SaveDocument(const twString& asFilePath);


	protected:
		virtual bool Parse(char* apString)=0;
		virtual char* Save()=0;

		virtual const char* GetErrorMsg()=0;
	};

}
#endif // JSONDOCUMENT_H
