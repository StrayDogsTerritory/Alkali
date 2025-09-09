#ifndef ALK_LOGWRITER_H
#define ALK_LOGWRITER_H

#pragma warning(disable: 4996) // disable deprecation warning for _wfopen and vsprintf

#include "system\String.h"
#include "system\SystemTypes.h"
#include "stdio.h"

#include "system/Platform.h"
#define NORETURN
namespace alk {
	//----------------------------

	class cLogWriter
	{
	public:
		cLogWriter(const twString &asDefaultFile);
		~cLogWriter();

		void Write(const tString &asMessage);
		void Clear();

		void SetFileName(const twString& asFile);

	private:

		void ReopenFile();


		FILE* mpFile;
		twString msFileName;

	};
	//----------------------------

	extern void SetLogFile(const twString& asFile);

	extern void Log(const char* asMessage, ...);
	extern void sLog(const char* asMessage, ...);

	extern void Error(const char* asMessage, ...);

	extern void Warning(const char* asMessage, ...);

	extern void Debug(const char* asMessage, ...);

	extern  void  FatalError(const char* asMessage, ...) NORETURN;

}

#endif
