#ifndef ALK_JSONDOCUMENTCJSON_H
#define ALK_JSONDOCUMENTCJSON_H

#include "json/JsonDocument.h"

#include <json/cJson/cJSON.h>

namespace alk {

	class cJsonDocumentCJSON : public iJsonDocument
	{
	public:
		cJsonDocumentCJSON();
		~cJsonDocumentCJSON();

		void Parse(char* apString);

		void ConvertToString(cJSON* apJSON)
	};

}

#endif
