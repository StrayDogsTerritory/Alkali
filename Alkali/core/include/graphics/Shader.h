#ifndef ALK_SHADER_H
#define ALK_SHADER_H

#include "system/String.h"
 

#include "resources/ResourceBase.h"
namespace alk {

	enum eShaderType
	{
		eShaderType_eVertexShader,
		eShaderType_ePixelShader,
		
		////////////
		// Don't think these are used in OGL at all... EDIT: very, *very* wrong about this... please make fun of me
		eShaderType_eGeometryShader,
		eShaderType_eTessellationShader,
		eShaderType_eComputeShader

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
