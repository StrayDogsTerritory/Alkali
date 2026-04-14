#ifndef ALK_JSONDOCUMENT_H
#define ALK_JSONDOCUMENT_H

/*
* Created By: Simon Stroomer
*
* Implementation-agnostic json document class.
* Holds all the neccisary data in memory. 
* Can be read from and written to, will affect the physical file as well
* 
*/

#include "system/SystemTypes.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

#include <map>
#include <list>

namespace alk {


	//-----------------------------------------------------------------

	enum eJsonObjectType //UNUSED -type of object class is
	{
		eJsonObjectType_Object, // object object
		eJsonObjectType_Array, // array object
		eJsonObjectType_LastEnum
	};

	//-----------------------------------------------------------------

	typedef std::multimap<tString, tString> tMapValues; // value map of JSON document type definition
	typedef tMapValues::iterator tMapValIterator; // value map iterator type definition

	//-----------------------------------------------------------------

	class cJsonObject
	{
	public:
		cJsonObject(const tString& asName) : mpParent(NULL), msName(asName){} // constructor
		~cJsonObject(); // destructor

		//-----------------------------------------------------------------

		cJsonObject* GetChildObject(const tString& asName); // gets pointer to a child of current object

		//-----------------------------------------------------------------

		cJsonObject* CreateChildObject(const tString& asName); // creates a child object
		void DestroyChildObject(const tString& asName); // removes a child object
		
		//-----------------------------------------------------------------

		void SetValue(const tString& asName, const tString asVal); // sets the named value in the value map to the specified value

		void SetValueString(const tString& asName, const tString& asValue, const tString& asFallBack = "");// the specified value from a string

		void SetValueInt(const tString& asName, int alX, const tString& asFallBack = "");// the specified value from an int

		void SetValueFloat(const tString& asName, float afX, const tString& asFallBack = "");// the specified value from a float

		void SetValueBool(const tString& asName, bool abX, const tString& asFallBack = "");// the specified value from a boolean

		void SetValueVector2l(const tString& asName, tVector2l avVec, const tString& asFallback = "");// the specified value from a vector2l

		void SetValueVector2f(const tString& asName, tVector2f avVec, const tString& asFallback = "");// the specified value from a vector2f

		void SetValueVector3l(const tString& asName, tVector3l avVec, const tString& asFallback = "");// the specified value from a vector3l

		void SetValueVector3f(const tString& asName, tVector3f avVec, const tString& asFallback = "");// the specified value from a vector 3f

		//-----------------------------------------------------------------

		tString GetValue(const tString& asName);// gets the named value in the value map

		tString GetValueString(const tString& asName, const char* asFallback = ""); // gets the named string value

		int GetValueInt(const tString& asName, int alFallback=0);// gets the named integer value

		float GetValueFloat(const tString& asName, float afFallback=0.0f);// gets the named float value

		bool GetValueBool(const tString& asName, bool abFallback = false);// gets the named bool value

		tVector2l GetValueVector2l(const tString& asName, tVector2l avFallback = 0);// gets the named Vector2l value

		tVector2f GetValueVector2f(const tString& asName, tVector2f avFallback = 0);// gets the named Vector2f value

		tVector3l GetValueVector3l(const tString& asName, tVector3l avFallback = 0);// gets the named Vector3l value

		tVector3f GetValueVector3f(const tString& asName, tVector3f avFallback = 0);// gets the named Vector3f value

		//-----------------------------------------------------------------

		tString msName; // name

		cJsonObject* mpParent; // parent object

		std::list<cJsonObject*> mLstChildren; // list of children

		tMapValues mMapValues; // value map
	
	private:
		void AddChild(cJsonObject* apObject); // un-exposed function. Add a created object as a child
	};

	
	class iJsonDocument : public cJsonObject
	{
	public:
		iJsonDocument(const tString& asName); // constructor
		~iJsonDocument(); //destructor
		//-----------------------------------------------------------------

		bool LoadDocument(const twString& asFilePath); // standard file loading function
		bool SaveDocument(const twString& asFilePath); // standard file saving funtion

		//-----------------------------------------------------------------


	protected:
		virtual bool Parse(char* apString)=0; // virtual: impletation-specific file loading
		virtual char* Save()=0;// virtual: impletation-specific file saving

		//-----------------------------------------------------------------

		virtual const char* GetErrorMsg()=0; // UNUSED -virtual: implementation-specific error reporting
	};

}
#endif // JSONDOCUMENT_H
