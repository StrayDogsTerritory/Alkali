#ifndef ALK_SHADER_H
#define ALK_SHADER_H

#include "system/String.h"
#include <GL/glew.h> 

namespace alk {

	enum eShaderType
	{
		eVertexShader,
		ePixelShader

	};


	class iShader
	{
	public:
		virtual ~iShader() {};
		virtual bool CreateShader(const tString& asShader, eShaderType aeShaderType, iShader *pShader)=0;
		virtual void DestroyShader(iShader* apShader)  = 0;
		virtual bool ReloadShader() = 0;
		virtual GLenum GetShaderType(eShaderType aeShaderType) = 0;
	private:
		
	};

}
#endif
