#ifndef ALK_JSONDOCUMENT_H
#define ALK_JSONDOCUMENT_H

#include "system/String.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

#include <map>

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

		void AddChild(cJsonObject* apObject);

		tString GetValueString(const tString& asName, const char* asFallback);
		int GetValueInt(const tString& asName, int alFallback);
		float GetValueFloat(const tString& asName, float afFallback);
		bool GetValueBool(const tString& asName, bool abFallback);
		tVector2l GetValueVector2l(const tString& asName, size_t alIdx = 0);
		tVector2f GetValueVector2f(const tString& asName, size_t alIdx = 0);
		tVector3l GetValueVector3l(const tString& asName, size_t alIdx = 0);
		tVector3f GetValueVector3f(const tString& asName, size_t alIdx = 0);

		tString msName;

		cJsonObject* mpParent;

		std::list<cJsonObject*> mLstChildren;

		tMapValues mMapValues;
	};


	class iJsonDocument : public cJsonObject
	{
	public:
		iJsonDocument(const tString& asName);
		~iJsonDocument();

		bool LoadDocument(const twString& asFilePath);
		void SaveDocument(const twString& asFilePath);

		virtual bool Parse(char* apString) = 0;
	};

}
#endif // JSONDOCUMENT_H
