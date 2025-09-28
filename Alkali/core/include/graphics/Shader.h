#ifndef ALK_SHADER_H
#define ALK_SHADER_H

#include "system/String.h"
#include <GL/glew.h> 

#include "resources/ResourceBase.h"
namespace alk {

	enum eShaderType
	{
		eVertexShader, 
		ePixelShader, 
		
		////////////
		// Don't think these are used in OGL at all...
		eGeometryShader,
		eTessellationShader,
		eComputeShader 

	};


	class iShader : public iResourceBase
	{
	public:
		iShader(const tString& asName, const twString asPath, eShaderType aeType) : iResourceBase(asName, asPath)
		{
			meShaderType = aeType;
		}
		virtual ~iShader() {};

		virtual bool CreateFromFile(const twString& asFile)=0;
		virtual bool CreateFromString(const char* apString)=0;
		
		eShaderType GetShaderType() const { return meShaderType; }

	protected:
		eShaderType meShaderType;
	};

}
#endif
