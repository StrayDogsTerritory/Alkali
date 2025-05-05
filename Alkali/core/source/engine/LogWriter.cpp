#pragma warning(disable: 4996) // disable deprecation warning for _wfopen and vsprintf

#include "stdio.h"
#include <cstdarg>

#include "engine/LogWriter.h"

namespace alk {

	/////////////////////////////////////////////////////
	//	LOG WRITER	
	/////////////////////////////////////////////////////

	//----------------------------

	static cLogWriter LogFile(L"alkali.log");

	//----------------------------

	cLogWriter::cLogWriter(const twString& asFile)
	{
		mpFile = NULL;
		msFileName = asFile;
	}

	//----------------------------

	cLogWriter::~cLogWriter()
	{
		if (mpFile)
			fclose(mpFile);
	}

	//----------------------------

	void cLogWriter::SetFileName(const twString& asFile)
	{
		if (msFileName == asFile)
			return;	
		msFileName = asFile;
		if (mpFile)
			ReopenFile();
	}

	//----------------------------

	void cLogWriter::ReopenFile()
	{
		if (mpFile)
			fclose(mpFile);
		mpFile = _wfopen(msFileName.c_str(),L"W");
	}

	//----------------------------

	void cLogWriter::Write(const tString& asMessage)
	{
		if (mpFile == NULL)
			ReopenFile();
		if (mpFile)
		{
			fprintf(mpFile, "%s\n", asMessage.c_str());
			fflush(mpFile);
		}
	}

	//----------------------------
	// LOG FUNCTION
	//----------------------------

	void SetLogFile(const twString& asFile)
	{
		LogFile.SetFileName(asFile);
	}


	void Log(const char* asMessage, eMessageType eType, ...)
	{
		char Text[4096];
		va_list ap;
		if (asMessage == NULL)
			return;	
		va_start(ap, asMessage);
		vsprintf(Text, asMessage, ap);
		va_end(ap);

		tString sMessage;
		switch (eType)
		{
		case eTypeNormal:
			sMessage = "";
			break;
		case eTypeError:
			sMessage = "Error: ";
			break;
		case eTypeWarning:
			sMessage = "Warning: ";
			break;
		case eTypeFatalError:
			sMessage = "Fatal Error: ";
			break;
		case eTypeDebug:
			sMessage = "Debug: ";
			break;
		}
		sMessage += Text;
		LogFile.Write(sMessage);

		if (eType == eTypeFatalError)
		{
			//@TODO: make this spit out a fatal error message box. and kill SDL when I add it to the project... which I should have already done...
			exit(1);
		}
	}

	
}