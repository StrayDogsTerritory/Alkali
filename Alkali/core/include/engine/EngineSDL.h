#ifndef ALK_ENGINESDL_H
#define ALK_ENGINESDL_H

#include "engine/EngineSetupInterface.h"

namespace alk {

	class iVideo;
	class cVideo;

	class cSDLEngine : public iEngineSetup
	{
	public:
		cSDLEngine();
		~cSDLEngine();

		cVideo* CreateVideoModule();

	private:

		iVideo* mpVideoSDL;

	};

}
#endif