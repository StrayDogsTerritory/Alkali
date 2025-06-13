#ifndef ALK_SHADER_H
#define ALK_SHADER_H

namespace alk {

	enum eShaderType
	{
		eVertexShader,
		ePixelShader

	};


	class iShader
	{
	public:
		virtual ~Shader()
		virtual bool CreateShader(eShaderType aeShaderType)
		virtual iShader* DestroyShader(iShader* apShader)

	private:

	};

}
#endif
