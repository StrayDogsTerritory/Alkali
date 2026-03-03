#ifndef OZY_INPUTTESTDELETEME_H
#define OZY_INPUTTESTDELETEME_H
#include "BaseGame.h"

#include "OZYMain.h"

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
