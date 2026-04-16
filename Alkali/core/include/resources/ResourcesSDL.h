#ifndef ALK_RESOURCESSDL_H
#define ALK_RESOURCESSDL_H

#include "resources/ResourceInterface.h"

/*
* Created by Simon Stroomer
* low level initialization of DevIL and its loaders
*/

namespace alk {

	class cResourcesSDL : public iResources
	{
	public:

		//-------------------------------------------------------------------------------------
		cResourcesSDL(); // constructor
		~cResourcesSDL(); // destructor
		//-------------------------------------------------------------------------------------

		bool Init(); // initialize

		//-------------------------------------------------------------------------------------

		void SetupBitmapLoader(iResourceLoader* apResourceLoader); // sets up the bitmap

		//-------------------------------------------------------------------------------------
	};

}

#endif