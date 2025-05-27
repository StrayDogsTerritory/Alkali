#ifndef ALK_ENGINESETUPINTERFACE_H
#define ALK_ENGINESETUPINTERFACE_H

namespace alk {

	class cVideoSDL;
	class cVideo;

	class iEngineSetup
	{
	public:
		iEngineSetup() {};
		virtual ~iEngineSetup(){}


		virtual cVideo* CreateVideoModule()=0;
	};

}
#endif
