#ifndef ALK_SHADERGLSL_H
#define ALK_SHADERGLSL_H

#include "GL\glew.h"

#include "graphics/Shader.h"
#include "system/String.h"
#include <map>

namespace alk {

	

	class cGLSLShader : public iShader
	{ 
	public:
		cGLSLShader(const tString& asShader, eShaderType aeShaderType, cGLSLShader* pShader);
		~cGLSLShader();

		bool CreateShader(eShaderType aeShaderType);
		void DestroyShader(iShader* apShader);

		bool CompileShader(iShader* pShader);
		bool ReloadShader();

		

	private:
		tString msName;
		eShaderType meShaderType;
		

	};

	
}

#endif
