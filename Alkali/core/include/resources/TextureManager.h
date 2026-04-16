#ifndef ALK_TEXTUREMANAGER_H
#define ALK_TEXTUREMANAGER_H

#include "resources/ResourceManager.h"

namespace alk {

	class iTexture;
	class cResources;
	class cGraphics;

	class cTextureManager : public iResourceManager
	{
	public:

		//-------------------------------------------------------------------------------------

		cTextureManager(cResources* apResources, cGraphics* apGraphics); //constructor
		~cTextureManager(); //destructor

		//-------------------------------------------------------------------------------------

		iTexture* Create2DTexture(const tString& asName); //create 2D texture

		//-------------------------------------------------------------------------------------

		void Unload(iResourceBase* apResource) {}//UNUSED
		void Delete(iResourceBase* apResource);//UNUSED
		void Reload(iResourceBase* apResource) {}//UNUSED
		void Preload(iResourceBase* apResource) {}//UNUSED

		//-------------------------------------------------------------------------------------

	private:
		cResources* mpResources; // pointer to the resources module
		cGraphics* mpGraphics; //pointer to the graphics module

		//-------------------------------------------------------------------------------------

		iTexture* CreateImageTexture(const tString& asName); //UNUSED
		
		//-------------------------------------------------------------------------------------
	};

}

#endif
