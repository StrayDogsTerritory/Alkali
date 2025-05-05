#include "stdafx.h"
#include <stdio.h>


int AlkaliMain(const alk::tString &asCommandLine)
{
	alk::Log("This is a Normal Message!\n");
	alk::Log("This is a Warning Message!\n", alk::eMessageType::eTypeWarning);
	alk::Log("This is a Normal Message!\n", alk::eMessageType::eTypeWarning);
	alk::Log("This is a Normal Message!\n", alk::eMessageType::eTypeWarning);
	return 0;

}