#ifndef ALK_ENGINESETUPINTERFACE_H
#define ALK_ENGINESETUPINTERFACE_H

namespace alk {

	class cVideoSDL;

	class iEngineSetup
	{
	public:
		virtual ~iEngineSetup(){}


		virtual cVideoSDL* CreateVideoModule()=0;
	};

}
#endif
