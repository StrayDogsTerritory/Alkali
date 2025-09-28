#include "resources/ResourceBase.h"

namespace alk {

	iResourceBase::iResourceBase(const tString& asName, const twString& asFullPath)
	{
		msName = asName;
		msPath = asFullPath;
		mlUserCount = 0;
		mlID = 0;
	}

	iResourceBase::~iResourceBase()
	{ 
	}
}