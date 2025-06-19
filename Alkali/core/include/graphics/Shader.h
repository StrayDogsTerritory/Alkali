#ifndef ALK_SHADER_H
#define ALK_SHADER_H

#include "system/String.h"
#include <GL/glew.h> 

namespace alk {

	/////////////////////////////////
	// bad, because not all APIs have these types, should make this moduler
	
	enum eShaderType
	{
		eVertexShader,
		ePixelShader,
		eGeometryShader,
		eTessellationShader,
		eComputeShader 

	};


	class iShader
	{
	public:
		virtual ~iShader() {};
		virtual bool CreateShader(const tString& asShader, eShaderType aeShaderType, iShader *pShader)=0;
		virtual void DestroyShader(iShader* apShader)  = 0;
		virtual bool ReloadShader() = 0;
		// Don't do this its GL code in the master class
		//virtual GLenum GetShaderType(eShaderType aeShaderType) = 0;
		
	protected:
		
	};

}
#endif
