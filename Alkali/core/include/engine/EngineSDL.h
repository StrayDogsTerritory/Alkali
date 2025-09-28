#ifndef ALK_ENGINESDL_H
#define ALK_ENGINESDL_H

#include "engine/EngineSetupInterface.h"
#include "system/FlagBits.h"

namespace alk {

	class iGraphics;
	class cGraphics;

	class cSDLEngine : public iEngineSetup
	{
	public:
		cSDLEngine(tFlag alSetupFlags);
		~cSDLEngine();

		cGraphics* CreateGraphicsModule();

	private:

		iGraphics* mpGraphicsSDL;

	};

}
#endif