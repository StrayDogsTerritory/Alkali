#ifndef ALK_SHADERMANAGER_H	
#define ALK_SHADERMANAGER_H

#include <map>
#include "system/String.h"

#include "resources/ResourceManager.h"

#include "graphics/Shader.h"

namespace alk {

	class iShader;
	class iGpuProgram;
	class cGraphics;

	class cShaderManager : public iResourceManager
	{
	public:
		cShaderManager(cGraphics* apGraphics, cResources* apResources);
		~cShaderManager();
		
		
		iShader* CreateShader(const tString& asName, eShaderType aShaderType);

		void Unload(iResourceBase* apResource) {}
		void Delete(iResourceBase* apResource);
		void Reload(iResourceBase* apResource) {}
		void Preload(iResourceBase* apResource) {}

	private:
		cGraphics* mpGraphics;
		cResources* mpResources;
	};
}
#endif
