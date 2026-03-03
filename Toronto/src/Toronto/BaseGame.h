#ifndef OZY_BASEGAME_H
#define OZY_BASEGAME_H

#include "InputTestDELETEWHENDONE.h"
#include "OzyMain.h"

class cActionTest;

class cOzyGameBase
{
public:
	cOzyGameBase();
	~cOzyGameBase();

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


extern cOzyGameBase* gpBase;

#endif 

