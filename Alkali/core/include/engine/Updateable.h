#ifndef ALK_UPDATEABLE_H
#define ALK_UPDATEABLE_H

#include "system/String.h"

namespace alk {

	enum eUpdatableMessageType
	{
		eUpdateableMessageType_OnStart,
		eUpdateableMessageType_OnExit,
		eUpdateableMessageType_OnQuit,
		eUpdateableMessageType_OnPostBufferSwap,
		eUpdateableMessageType_OnRender,
		eUpdateableMessageType_OnPostRender,
		eUpdateableMessageType_OnPreUpdate,
		eUpdateableMessageType_OnUpdate,
		eUpdateableMessageType_OnPostUpdate,
		eUpdateableMessageType_OnPause,
		eUpdateableMessageType_Reset,
		eUpdateableMessageType_DeviceAdded,
		eUpdateableMessageType_DeviceRemoved,
		eUpdateableMessageType_AppGainedFocus,
		eUpdateableMessageType_AppLostFocus,

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

		virtual void DeviceAdded() {}
		virtual void DeviceRemoved() {}

		virtual void AppGainedFocus() {}
		virtual void AppLostFocus() {}

		void CallMessage(eUpdatableMessageType aType, float afStep)
		{
			switch (aType)
			{
			case eUpdateableMessageType_OnStart: 
				OnStart(); break;
			case eUpdateableMessageType_OnExit:
				OnExit(); break;
			case eUpdateableMessageType_OnQuit:
				OnQuit(); break;
			case eUpdateableMessageType_OnPostBufferSwap:
				OnPostBufferSwap(); break;
			case eUpdateableMessageType_OnPreUpdate:
				OnPreUpdate(afStep); break;
			case eUpdateableMessageType_OnUpdate:
				OnUpdate(afStep); break;
			case eUpdateableMessageType_OnPostUpdate:
				OnPostUpdate(afStep); break;
			case eUpdateableMessageType_OnPause:
				OnPause(afStep); break;
			case eUpdateableMessageType_Reset:
				Reset(); break;
			case eUpdateableMessageType_DeviceAdded:
				DeviceAdded(); break;
			case eUpdateableMessageType_DeviceRemoved:
				DeviceRemoved(); break;
			case eUpdateableMessageType_AppGainedFocus:
				DeviceAdded(); break;
			case eUpdateableMessageType_AppLostFocus:
				DeviceAdded(); break;
			}
		}

	private:
		tString msName;
	};

}

#endif
