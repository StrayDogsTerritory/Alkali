#ifndef ALK_JSONDOCUMENTCJSON_H
#define ALK_JSONDOCUMENTCJSON_H

/*
*  Json Document.h 
* Created by: Simon Stroomer
*  Derived class that reads and writes JSON files via the cJSON library
*  is created when cResources::CreateJsonDocument is called, though the funtion returns the parent class.
*/
#include "json/JsonDocument.h"

#include <json/cJson/cJSON.h>

namespace alk {

	class cJsonDocumentCJSON : public iJsonDocument
	{
	public:
		cJsonDocumentCJSON(const tString& asName); // constructor

		//-----------------------------------------------------------------

		~cJsonDocumentCJSON(); // destructor

		//-----------------------------------------------------------------

	private:
		//-----------------------------------------------------------------

		bool Parse(char* apString); // implementation-specific loading

		//-----------------------------------------------------------------

		char* Save(); // implementation-specific saving

		//-----------------------------------------------------------------

		bool LoadJsonObject(cJSON* apJSON, cJsonObject* apObject); // load Objects recursively
		bool SaveJsonObject(cJSON* apJSON, cJsonObject* apObject); // load Objects recursively

		//-----------------------------------------------------------------

		tString ConvertToString(cJSON* apJSON); // converts cJSON values to std::string

		//-----------------------------------------------------------------

		float inline GetNumber(cJSON* apJSON); // kinda bad, but casts ints and doubles into floats
		
		//-----------------------------------------------------------------

		const char* GetErrorMsg(); // UNUSED =returns cJSON error message
	};

}
#endif
