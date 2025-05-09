#ifndef ALK_MUTEX_H
#define ALK_MUTEX_H

namespace alk {

	class iMutex
	{
	public:
		iMutex();
		virtual ~iMutex() {}

		virtual bool Lock() = 0;
		virtual bool Unlock() = 0;
	};

}
#endif
