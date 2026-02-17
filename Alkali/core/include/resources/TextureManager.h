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
		cTextureManager(cResources* apResources, cGraphics* apGraphics);
		~cTextureManager();

		iTexture* Create2DTexture(const tString& asName);


		void Unload(iResourceBase* apResource) {}
		void Delete(iResourceBase* apResource);
		void Reload(iResourceBase* apResource) {}
		void Preload(iResourceBase* apResource) {}

	private:
		cResources* mpResources;
		cGraphics* mpGraphics;

		iTexture* CreateImageTexture(const tString& asName);
	};

}

#endif
