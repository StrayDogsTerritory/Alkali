#ifndef ALK_JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include "system/String.h"


namespace alk {

	class iJsonDocument
	{
	public:
		iJsonDocument();
		~iJsonDocument();

		void Parse(const twString &asPath);


	};

}
#endif // JSONDOCUMENT_H
