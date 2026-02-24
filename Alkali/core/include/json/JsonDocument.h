#ifndef ALK_JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include "system/String.h"

#include <map>
#include <vector>

namespace alk {

	class cJsonValue
	{
	public:
		cJsonValue(const tString& asName, const tString& asValue);
		~cJsonValue();
		
		tString msName;
		std::vector<tString> mvValue;
	};

	class cJsonObject
	{
	public:
		cJsonObject();
		~cJsonObject();

	private:
		std::map<tString, tString> mMapJsonValue;

	};


	class iJsonDocument
	{
	public:
		iJsonDocument();
		~iJsonDocument();

		void Parse(const twString &asPath);


	};

}
#endif // JSONDOCUMENT_H
