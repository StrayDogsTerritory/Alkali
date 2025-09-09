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
		ePixelShader, // <- also known in OGL as a fragment shader. Keeping it vague incase I add d3D support.
		////////////
		// Don't think these are used in OGL at all...
		eGeometryShader,
		eTessellationShader,
		eComputeShader 

	};


	class iShader
	{
	public:
		virtual ~iShader() {};
		virtual bool CreateShader(const twString& asShader, eShaderType aeShaderType)=0;
		virtual void DestroyShader(iShader* apShader)  = 0;
		virtual bool ReloadShader() = 0;

		virtual	GLenum GetShaderType(eShaderType aeShaderType) = 0;

		int GetShaderID() { return mlShaderID; }

		// Don't do this its GL code in the master class
		//virtual GLenum GetShaderType(eShaderType aeShaderType) = 0;
		
	protected:
		unsigned int mlShaderID;
		eShaderType meShaderType;
	};

}
#endif
