#ifndef ALK_ENGINESETUPINTERFACE_H
#define ALK_ENGINESETUPINTERFACE_H

namespace alk {

	class cResources;
	class cGraphicsSDL;
	class cGraphics;
	class cSystem;
	class cInput;
	class iEngineSetup
	{
	public:
		virtual ~iEngineSetup(){}


		virtual cGraphics* CreateGraphicsModule()=0;
		virtual cSystem* CreateSystemModule()=0;
		virtual cInput* CreateInputModule()=0;
		virtual cResources* CreateResourcesModule()=0;
	};

}
#endif
