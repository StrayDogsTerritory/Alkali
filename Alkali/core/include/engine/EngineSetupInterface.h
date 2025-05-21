#ifndef ALK_ENGINESETUPINTERFACE_H
#define ALK_ENGINESETUPINTERFACE_H

class cVideoSDL;


class iEngineSetup
{
	virtual ~iEngineSetup(){}


	cVideoSDL* CreateVideoModule();
};


#endif
