#ifndef ALK_UPDATEABLE_H
#define ALK_UPDATEABLE_H

#include "system/String.h"

namespace alk {

	enum eUpdatableMessageType
	{
		eUpdatableMessageType_OnStart,
		eUpdatableMessageType_OnExit,
		eUpdatableMessageType_OnQuit,
		eUpdatableMessageType_OnPostBufferSwap,
		eUpdatableMessageType_OnRender,
		eUpdatableMessageType_OnPostRender,
		eUpdatableMessageType_OnPreUpdate,
		eUpdatableMessageType_OnUpdate,
		eUpdatableMessageType_OnPostUpdate,
		eUpdatableMessageType_OnPause,
		eUpdatableMessageType_Reset,

		eUpdatableMessageType_LastEnum

	};

	class iUpdateable
	{
	public:
		iUpdateable(const tString& asName) : msName(asName) {}
		virtual ~iUpdateable() {}

		virtual void OnStart() {}
		virtual void OnExit() {}
		virtual void OnQuit() {}

		virtual void OnPostBufferSwap() {}

		virtual void OnPreUpdate(float afStep) {}
		virtual void OnUpdate(float afStep) {}
		virtual void OnPostUpdate(float afStep) {}
		virtual void OnPause(float afStep) {}

		virtual void Reset() {}

		void CallMessage(eUpdatableMessageType aType, float afStep)
		{
			switch (aType)
			{
			case eUpdatableMessageType_OnStart: 
				OnStart(); break;
			case eUpdatableMessageType_OnExit:
				OnExit(); break;
			case eUpdatableMessageType_OnQuit:
				OnQuit(); break;
			case eUpdatableMessageType_OnPostBufferSwap:
				OnPostBufferSwap(); break;
			case eUpdatableMessageType_OnPreUpdate:
				OnPreUpdate(afStep); break;
			case eUpdatableMessageType_OnUpdate:
				OnUpdate(afStep); break;
			case eUpdatableMessageType_OnPostUpdate:
				OnPostUpdate(afStep); break;
			case eUpdatableMessageType_OnPause:
				OnPause(afStep); break;
			case eUpdatableMessageType_Reset:
				Reset(); break;
			}
		}

	private:
		tString msName;
	};

}

#endif
