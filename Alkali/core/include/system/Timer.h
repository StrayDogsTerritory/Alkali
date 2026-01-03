#ifndef ALK_TIMER_H
#define ALK_TIMER_H

namespace alk {

	class iTimer
	{
	public:
		iTimer(int alDuration) { mlMaxDuration = alDuration; }

		~iTimer() {}

		void Update();

		void Reset();

	private:
		int mlMaxDuration;
		unsigned int mlCurrentTime;
	};

}

#endif
