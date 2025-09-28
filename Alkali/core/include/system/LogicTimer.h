#ifndef ALK_LOGICTIMER_H
#define ALK_LOGICTIMER_H

namespace alk {

	class cLogicTimer
	{
	public:
		cLogicTimer(int alUpdatesPerSecond);
		~cLogicTimer();

		bool CanUpdate();

		void Reset();

		void SetUpdatesPerSecond(int alUpdateRate);
		int GetUpdatesPerSecond();

		double GetTime() { return mfTime; }
		double GetTimeAdd() { return mfTimeAdd; }

		float GetStepSize();

		void Update();

		void EndLoop();

	private:
		 int mlUpdateRate;
		 int mlMaxUpdates;
		 int mlUpdateCount;

		double mfTime;
		double mfTimeAdd;
	};

}

#endif
