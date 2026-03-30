#ifndef ALK_JSONDOCUMENTCJSON_H
#define ALK_JSONDOCUMENTCJSON_H

#include "json/JsonDocument.h"

#include <json/cJson/cJSON.h>

namespace alk {

	class cJsonDocumentCJSON : public iJsonDocument
	{
	public:
		cJsonDocumentCJSON(const tString& asName);
		~cJsonDocumentCJSON();


	public:
		bool Parse(char* apString);
		char* Save();

		bool LoadJsonObject(cJSON* apJSON, cJsonObject* apObject);
		bool SaveJsonObject(cJSON* apJSON, cJsonObject* apObject);

		tString ConvertToString(cJSON* apJSON);

		float inline GetNumber(cJSON* apJSON);
		

		const char* GetErrorMsg();
	};

}
#endif
