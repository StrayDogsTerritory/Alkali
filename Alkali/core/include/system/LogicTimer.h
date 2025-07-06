#ifndef ALK_LOGICTIMER_H
#define ALK_LOGICTIMER_H

#include "engine/LogWriter.h"

//============================================================
//---------------------------------------------------------
//////////////////////////////////////////////////////////////
// debug timing 
//////////////////////////////////////////////////////////////
//---------------------------------------------------------
//=============================================================
#define START_TIMING(x) \
	unsigned long x##_initial = alk::cPlatform::GetAppTime();

#define END_TIMING(x) \
	unsigned long x##_final = alk::cPlatform::GetAppTime(); \
	unsigned long x##_delta = x##_final - x##_initial;

//-----------------------------------------------------------------

#define START_TIMING_COMP(x,y) \
	unsigned long x##_initial = alk::cPlatform::GetAppTime(); \
	unsigned long y##_initial = alk::cPlatform::GetAppTime();

#define END_TIMING_COMP(x,y) \
	unsigned long x##_final = alk::cPlatform::GetAppTime(); \
	unsigned long y##_final = alk::cPlatform::GetAppTime(); \
	unsigned long x##_delta = x##_final - x##_initial; \
	unsigned long y##_delta = y##_final - y##_initial; \
	alk::cLogWriter::WriteDebug("Timing: %d took %d ms, %d took %d ms",x##_initial, y##_initial x##_delta, y##_delta);


//============================================================
//---------------------------------------------------------
//////////////////////////////////////////////////////////////
// logic timer
//////////////////////////////////////////////////////////////
//---------------------------------------------------------
//=============================================================


class cLogicTimer
{
public:
	cLogicTimer(int alUpdatesPerSecond);
	~cLogicTimer();

	int GetUpdatesPerSecond();

	void SetUpdatesPerSecond(unsigned int alUpdatesPerSecond);

	void Reset();

private:
	unsigned int mlUpdatesPerSecond;
};


#endif //ALK_LOGICTIMER_H

