#include "graphics/Graphics.h"
#include "video/VideoSDL.h"
#include "system/MemoryManager.h"
#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "graphics/GPUProgram.h"
#include "graphics/GPUProgramGLSL.h"
#include "engine/LogWriter.h"
#include "system/String.h"
#include "system/Platform.h"
#include "system/SystemTypes.h"

#include "resources/FileSearcher.h"

#include "json/JsonDocument.h"

#include "SDL3/SDL.h"

namespace alk {

	cGraphics::cGraphics(tFlag alShadingLanguage)
	{
		cJsonDocument* pDoc = alkNew(cJsonDocument, ());
		pDoc->Parse(L"test\\panam.ent.json");
		alkDelete(pDoc);
	}

	cGraphics::~cGraphics()
	{
	
	}

	iShader* cGraphics::CreateShader(const tString& asName, eShaderType aeShaderType)
	{
		
		return alkNew(cGLSLShader, (asName, aeShaderType));
	}

	iGpuProgram* cGraphics::CreateProgram(const tString& asName)
	{
		return alkNew(cGLSLGpuProgram, (asName));
	}

	iShader* cGraphics::CreateShaderDifferentAndTemp(const tString& asName, eShaderType aeShaderType)
	{
		iShader* pShader = NULL;

		pShader = CreateShader(asName, aeShaderType);


		pShader->CreateShader(cString::ToWideChar(asName).c_str(), aeShaderType);

		return pShader;
	}

	iGpuProgram* cGraphics::CreateProgramWithShaders(const tString& asName, const tString& asPixelShader, const tString& asVertexShader)
	{
		iGpuProgram* pProgram = NULL;

		iShader* pVertexShader = CreateShaderDifferentAndTemp(asVertexShader, eVertexShader);
	
		iShader* pPixelShader = CreateShaderDifferentAndTemp(asPixelShader, ePixelShader);
		
		pProgram = CreateProgram(asName);
		pProgram->SetShaderType(eVertexShader, pVertexShader);
		pProgram->SetShaderType(ePixelShader, pPixelShader);
		pProgram->Link();

		return pProgram;
	}








}