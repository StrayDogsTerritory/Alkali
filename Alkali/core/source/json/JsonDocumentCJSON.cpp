#include "json/JsonDocumentCJSON.h"

#include "engine/LogWriter.h" // debugging

namespace alk {

	cJsonDocumentCJSON::cJsonDocumentCJSON(const tString& asName)
	: iJsonDocument(asName)
	{
		// does nothing
	}

	//-----------------------------------------------------------------

	cJsonDocumentCJSON::~cJsonDocumentCJSON()
	{
		// does nothing
	}

	//-----------------------------------------------------------------

	bool cJsonDocumentCJSON::Parse(char* apString)
	{
		cJSON* pRoot = cJSON_Parse(apString); // create root cJSON object, fuctions like a reference to document

		if (pRoot == NULL) return false; // if it can't be created, somethings gone wrong. Return!

		cJSON* pObject = pRoot->child; // this points to the first object of the file
	
		LoadJsonObject(pObject, this); // recursively load each sibling and their children within the file
		
		cJSON_Delete(pRoot); // free the file's memory

		return true;
	}

	//-----------------------------------------------------------------

	char* cJsonDocumentCJSON::Save()
	{
		cJSON* pRoot = cJSON_CreateObject(); // create root cJSON object, fuctions like a reference to document

		SaveJsonObject(pRoot, this);// recursively save each sibling and their children within the loaded document

		char* sRet = cJSON_Print(pRoot); // get formatted string to print into saving file

		cJSON_Delete(pRoot); // free the document's memory

		return sRet;

	}

	//-----------------------------------------------------------------

	bool cJsonDocumentCJSON::SaveJsonObject(cJSON* apJSON, cJsonObject* apObject)
	{
		std::list<cJsonObject*>::iterator it = apObject->mLstChildren.begin(); // create a list iterator

		for (; it != apObject->mLstChildren.end(); ++it) // loop through the list
		{
			cJSON* pChild = cJSON_CreateObject(); // create cJSON object

			cJsonObject* pChildObject = (*it);// dereferences the pointer of the value of the list at it

			tMapValues Map = pChildObject->mMapValues; // get the value map

			for (tMapValIterator it = Map.begin(); it != Map.end(); ++it)
			{
				cJSON_AddStringToObject(pChild, it->first.c_str(), it->second.c_str()); // add the values in the map to the newly created cJSON object
			}

			cJSON_AddItemToObject(apJSON, pChildObject->msName.c_str(), pChild); // add our now filled object to its parent

			// run this recursivly for each child
			SaveJsonObject(pChild, pChildObject); // run this function for every child in the original object's list
		}

		return true;
	}

	//-----------------------------------------------------------------

	bool cJsonDocumentCJSON::LoadJsonObject(cJSON* apJSON, cJsonObject* apObject)
	{

		while (apJSON != NULL) // loop through the file
		{
			if (apJSON->type == cJSON_Array) // arrays are not supported
			{
				Warning("Object '%s' could not be loaded! JSON arrays are not supported!\n", apJSON->string); //let the user know the array will not be loaded
				return false;
			}

			if (apJSON->type != cJSON_Object) // if the current object is not a child
			{
				apObject->mMapValues.insert(tMapValues::value_type(cString::toString(apJSON->string, ""), ConvertToString(apJSON))); // convert the value in the object to a std::string, and add it to the document
			}

			else // if it is a child
			{
				cJsonObject* pSubObject = apObject->CreateChildObject(cString::toString(apJSON->string, "")); // convert the name to a std::string and save it like so into the document

				cJSON* pJSONChild = apJSON->child; // get the pointer to the child of the current object

				while (pJSONChild != NULL) //loop through the current objects children
				{
					LoadJsonObject(pJSONChild, pSubObject); // recursively load the children and their values 

					pJSONChild = pJSONChild->child; // get the next child
				}
			}

			apJSON = apJSON->next; // get the next sibling
		}

		return true;
	}

	//-----------------------------------------------------------------

	tString cJsonDocumentCJSON::ConvertToString(cJSON* apJSON)
	{
		if (apJSON->type == cJSON_String) return cString::toString(apJSON->valuestring, ""); // call char* to std::string conversion
		else if (apJSON->type == cJSON_Number) return cString::ToStringFloat(GetNumber(apJSON), "0.0f");// call float to std::string conversion

		else return apJSON->type == cJSON_True ? "true" : "false"; // return string conversion of boolean value
	}

	//-----------------------------------------------------------------

	float inline cJsonDocumentCJSON::GetNumber(cJSON* apJSON)
	{
		if (apJSON->valueint != NULL) return (float)apJSON->valueint; // if the value is an integer, cast to float and return it
		else if (apJSON->valuedouble != NULL) return (float)apJSON->valuedouble; // if the value is a double, cast to float and return it

		return NULL; // if there's not value present, just return 0.0f
	}

	//-----------------------------------------------------------------

	const char* cJsonDocumentCJSON::GetErrorMsg()
	{
		return cJSON_GetErrorPtr(); // UNUSED: Doesn't format nicely, since it is always NULL
	}
}