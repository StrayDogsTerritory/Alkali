#ifndef ALK_ENGINESDL_H
#define ALK_ENGINESDL_H

#include "engine/EngineSetupInterface.h"
#include "system/FlagBits.h"

namespace alk {

	class iVideo;
	class cVideo;

	class cSDLEngine : public iEngineSetup
	{
	public:
		cSDLEngine(tFlag alEngineSetupFlags);
		~cSDLEngine();

		cVideo* CreateVideoModule();

	private:

		iVideo* mpVideoSDL;

	};

}
#endif