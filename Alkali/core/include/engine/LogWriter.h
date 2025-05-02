#ifndef ALK_LOGWRITER_H
#define ALK_LOGWRITER_H

#include "system\String.h"

namespace alk {

	enum eMessageType
	{
		eTypeNormal,
		eTypeWarning,
		eTypeError,
		eTypeFatalError,
		eTypeDebug
	};

	class cLogWriter
	{
	public:
		cLogWriter(const twString &asFile);
		~cLogWriter();

		void Write(const tString &asMessage);

	};


	void Log(const char* asMessage, eMessageType = eTypeNormal);


}
#endif
