#ifndef ALK_LOGWRITER_H
#define ALK_LOGWRITER_H

#include<stdio.h>
// I'm including it here temporarily, will move if I have to
#include "system/AlkString.h"


namespace alk
{
	class cLogWriter 
	{
	public:

		 cLogWriter(const twString& asDefaultFile);
		 ~cLogWriter();

		 void Write(const tString& asMessage);
		 void Clear();
		 void SetFileName(const twString& asFile);
	private:

		void ReopenFile();
		
		FILE* mpFile;
		twString msFileName;
	};


};

#endif