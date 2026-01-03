#ifndef ALK_MOUSESDL_H
#define ALK_MOUSESDL_H

#include "input/Mouse.h"

#include <vector>
#include <SDL3/SDL.h>

namespace alk {

	class cInputSDL;

	class cMouseSDL : public iMouse
	{
	public:
		cMouseSDL(cInputSDL* apInputSDL);
		~cMouseSDL();

		void Update();

		bool ButtonDown(eMouseButton aKey);

		bool MouseActive();

		tVector2l GetMousePos();

	private:
		bool mbActive;
		eMouseButton SDLToKey(int alKey);
		cInputSDL* mpInputSDL;
	
	};

} 

#endif
