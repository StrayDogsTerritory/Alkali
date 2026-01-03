#ifndef TOR_INPUTTESTDELETEME_H
#define TOR_INPUTTESTDELETEME_H

#include "BaseGame.h"

#include "TorMain.h"

class cActionTest : public iUpdateable
{
public:
	cActionTest();
	~cActionTest();

	void OnUpdate(float afStep);
private:
	cAction* mpAction;
};

#endif
