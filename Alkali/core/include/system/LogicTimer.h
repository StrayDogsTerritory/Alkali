#ifndef ALK_LOGICTIMER_H
#define ALK_LOGICTIMER_H

namespace alk {

	class cLogicTimer
	{
	public:
		cLogicTimer(unsigned int alUpdatesPerSecond);
		~cLogicTimer() {}

		bool WantUpdate();

		unsigned int GetupdatesPerSecond();
		void SetUpdatesPerSecond(unsigned int alUpdatesPerSecond);

		void Reset();
		void Update();

		void EndLoop();

		double GetUpdatesPerSec() const { return mfUpdatesPerSec; }

	private:
		double mfUpdatesPerSec;
		double mfCurrentTime;

		int mlMaxUpdates;
		int mlUpdateCount;
	};

}

#endif
