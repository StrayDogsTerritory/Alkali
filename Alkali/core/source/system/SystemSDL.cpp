#include "system/SystemSDL.h"

#include "engine/LogWriter.h"

namespace alk {

	cSystemSDL::cSystemSDL()
	{
		Log("-----Alkali Engine Log-----\n");
	}

	cSystemSDL::~cSystemSDL()
	{

	}

	iScript* cSystemSDL::CreateScript()
	{
		return NULL;
	}
}