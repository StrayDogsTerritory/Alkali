#ifndef ALK_ENGINESDL_H
#define ALK_ENGINESDL_H

#include "engine/EngineSetupInterface.h"
#include "system/FlagBits.h"

namespace alk {

	class iGraphics;
	class cGraphics;
	class cSystem;
	class iSystem;
	class cInput;
	class iInput;

	class cSDLEngine : public iEngineSetup
	{
	public:
		cSDLEngine(tFlag alSetupFlags);
		~cSDLEngine();

		cGraphics* CreateGraphicsModule();
		cSystem* CreateSystemModule();
		cInput* CreateInputModule();
	private:

		iGraphics* mpGraphicsSDL;
		iSystem* mpSystemSDL;
		iInput* mpInputSDL;

	};

}
#endif