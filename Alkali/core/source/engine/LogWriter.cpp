
#include "stdio.h"
#include <cstdarg>

#include "engine/LogWriter.h"

#include "SDL3/SDL.h"

namespace alk {

	/////////////////////////////////////////////////////
	//	LOG WRITER	
	/////////////////////////////////////////////////////

	//----------------------------

	static cLogWriter LogWriter(L"alkali.log");

	//----------------------------

	cLogWriter::cLogWriter(const twString& asFileName)
	{
		msFileName = asFileName;
		mpFile = NULL;
	}

	//----------------------------

	cLogWriter::~cLogWriter()
	{
		if (mpFile)
			fclose(mpFile);
	}

	//----------------------------

	void cLogWriter::Write(const tString& asMessage)
	{
		if (!mpFile)
			ReopenFile();

		if (mpFile)
		{
			fprintf(mpFile, "%s", asMessage.c_str());
			fflush(mpFile);
		}
	}

	//----------------------------

	void cLogWriter::Clear()
	{
		ReopenFile();
		if (mpFile) fflush(mpFile);
	}

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

		mpFile = _wfopen(msFileName.c_str(),L"w");
	}

	//----------------------------

	

	//----------------------------
	// LOG FUNCTION
	//----------------------------

	void SetLogFile(const twString& asFile)
	{
		LogWriter.SetFileName(asFile);
	}


	void Log(const char* asMessage,...)
	{
		char Text[4096];
		va_list ap;
		if (asMessage == NULL)
			return;
		va_start(ap, asMessage);
		vsprintf(Text, asMessage, ap);
		va_end(ap);

		tString sMessage = "";
		
			sMessage += Text;
			LogWriter.Write(sMessage);

		}

		void Error(const char* asMessage, ...)
		{
			char Text[4096];
			va_list ap;
			if (asMessage == NULL)
				return;
			va_start(ap, asMessage);
			vsprintf(Text, asMessage, ap);
			va_end(ap);
			tString sMessage = "[ERROR]: ";

			sMessage += Text;
			LogWriter.Write(sMessage);
		}

		void Warning(const char* asMessage, ...)
		{
			char Text[2048];
			va_list ap;
			if (asMessage == NULL)
				return;
			va_start(ap, asMessage);
			vsprintf(Text, asMessage, ap);
			va_end(ap);
			tString sMessage = "[Warning]: ";
			sMessage += Text;
			LogWriter.Write(sMessage);
		}

		void Debug(const char* asMessage, ...)
		{
			char Text[2048];
			va_list ap;
			if (asMessage == NULL)
				return;
			va_start(ap, asMessage);
			vsprintf(Text, asMessage, ap);
			va_end(ap);
			tString sMessage = "[Debug]: ";
			sMessage += Text;
			LogWriter.Write(sMessage);
		}

		///////////////////
		// Commenting this out until I have SDL exit up and running
		//	I've got this now!

		void FatalError(const char* asMessage, ...)
		{
			char Text[2048];
			va_list ap;
			if (asMessage == NULL)
				return;
			va_start(ap, asMessage);
			vsprintf(Text, asMessage, ap);
			va_end(ap);
			tString sMessage = "[FATAL ERROR!]: ";
			sMessage += Text;
			LogWriter.Write(sMessage);

			SDL_Quit();

			exit(1);
		}
	
}