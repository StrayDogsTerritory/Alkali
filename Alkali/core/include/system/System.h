#ifndef ALK_SYSTEM_H
#define ALK_SYSTEM_H

#include "system/String.h"
#include "engine/Updateable.h"

#include "json/JsonDocument.h"

namespace alk {
	
	class iSystem;
	class cLogicTimer;

	class cSystem : public iUpdateable
	{
	public:
		cSystem(iSystem* apSystemInterface);
		~cSystem();

		void OnUpdate(float afStep);

		iSystem* GetSystemInt() { return mpSystemInterface; }
		cLogicTimer* CreateLogicTimer(unsigned int alUpdateRate);

		void TestString();

	private:
		iSystem* mpSystemInterface;
		static int GetChecksumTest();

		int mlUpdateTest;
	};

}
#endif