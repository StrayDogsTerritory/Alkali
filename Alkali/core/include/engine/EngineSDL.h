#ifndef ALK_ENGINESDL_H
#define ALK_ENGINESDL_H

#include "engine/EngineSetupInterface.h"
#include "engine/Engine.h"

namespace alk {

	class cVideoSDL;


	class cSDLEngine : public iEngineSetup
	{
	public:
		cSDLEngine();
		~cSDLEngine();

		cVideoSDL* CreateVideoModule();

	private:


	};

}
#endif