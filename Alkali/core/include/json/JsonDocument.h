#ifndef ALK_JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include "system/String.h"

#include <vector>
#include <list>

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
		cJsonObject(const tString& msName);
		~cJsonObject();

		void AddObject(cJsonObject* apObject);;
		void RemoveObject(const tString& asName);
		
		cJsonObject* GetJsonObject(const tString& asName);

	private:
		tString msName;
		tString msValue;

		std::list<cJsonObject*> mLstJsonObject;

	};


	class iJsonDocument
	{
	public:
		iJsonDocument();
		~iJsonDocument();

		void Parse(const twString &asPath);

	private:
		std::list<cJsonObject*> mLstJsonObject;
	};

}
#endif // JSONDOCUMENT_H
