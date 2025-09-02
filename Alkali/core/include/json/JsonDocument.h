#ifndef ALK_JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include "json/JsonCPPWrapper.h"

#include "system/String.h"


namespace alk {

	class cJsonDocument
	{
	public:
		cJsonDocument();
		~cJsonDocument();

		void Parse(const twString &asPath);


	};

}
#endif // JSONDOCUMENT_H
