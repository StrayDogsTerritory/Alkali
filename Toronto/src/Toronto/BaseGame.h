#ifndef TOR_BASEGAME_H
#define TOR_BASEGAME_H

#include "InputTestDELETEWHENDONE.h"
#include "TorMain.h"

class cActionTest;

class cTorGameBase
{
public:
	cTorGameBase();
	~cTorGameBase();

	bool Init(const tString& asCommandLine);

	void Run();
	void Exit();

	cEngine* GetEngine() { return mpEngine; }

private:
	bool ParseCommandLine(const tString& asCommandLine);
	bool InitEngine();
	bool UserInit();
	bool InitGame();

	void ExitEngine();

	cEngine* mpEngine;

	cActionTest* mpA;
};


extern cTorGameBase* gpBase;

#endif 

