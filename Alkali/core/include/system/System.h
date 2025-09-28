#ifndef ALK_SYSTEM_H
#define ALK_SYSTEM_H

namespace alk {
	
	class iSystemInterface;
	class cLogicTimer;

	class cSystem
	{
	public:
		cSystem(iSystemInterface* apSystemInterface);
		~cSystem();

		iSystemInterface* GetSystemInt() { return apSystemInterface; }
		cLogicTimer* CreateLogicTimer(unsigned int alUpdateRate);

	private:
		iSystemInterface* apSystemInterface;
	};

}
#endif