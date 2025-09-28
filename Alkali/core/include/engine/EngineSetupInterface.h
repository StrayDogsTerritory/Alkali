#ifndef ALK_ENGINESETUPINTERFACE_H
#define ALK_ENGINESETUPINTERFACE_H

namespace alk {

	class cGraphicsSDL;
	class cGraphics;

	class iEngineSetup
	{
	public:
		virtual ~iEngineSetup(){}


		virtual cGraphics* CreateGraphicsModule()=0;
	};

}
#endif
