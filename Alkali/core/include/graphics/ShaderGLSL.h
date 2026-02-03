#ifndef ALK_SHADERGLSL_H
#define ALK_SHADERGLSL_H

#include "GL\glew.h"

#include "graphics/Shader.h"
#include "system/String.h"
#include <map>

#include <stdio.h>
namespace alk {

	

	class cGLSLShader : public iShader
	{ 
	public:
		cGLSLShader(const tString& asName, eShaderType aShaderType);
		~cGLSLShader();

		bool CreateFromFile(const twString& asFile);
		bool CreateFromString(const char* apString);

		void LogShaderError();

		bool Reload() { return false; }
		void Unload() {}
		void Destroy() {}

		GLuint GetHandle() const { return mlShaderID; }

	private:
		GLenum ConvertToGL( eShaderType aShaderType);
		GLuint mlShaderID;
	};

	
}

#endif
