#include "graphics/Graphics.h"
#include "system/MemoryManager.h"
#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "graphics/GPUProgram.h"
#include "graphics/GPUProgramGLSL.h"
#include "engine/LogWriter.h"
#include "system/String.h"

#include "graphics/GraphicsInterface.h"

#include "resources/Resources.h"
#include "resources/ResourceManager.h"
#include "resources/ShaderManager.h"
#include "resources/Filesearcher.h"

namespace alk {

	cGraphics::cGraphics(iGraphics* apGraphics)
	{	
		mpGraphics = apGraphics;
	}

	cGraphics::~cGraphics()
	{
		Log("Beginning cGraphics Destructor\n");

		DeleteAll(lProgramList);

		Log("Ending cGraphics Destructor\n");
	}

	bool cGraphics::Init(cResources* apResources, int alHeight, int alWidth, int alWindowMode)
	{
		mpResources = apResources;
		mpGraphics->Init(alHeight, alWidth, alWindowMode);

		//CreateShaderProgram("testProgram", "testShader_Frag.glsl", "testShader_Vert.glsl");
		mpResources->AddDirectory(L"test/shaders", true);
		return true;
	}

	iGpuProgram* cGraphics::CreateProgram(const tString& asName)
	{
		iGpuProgram* pProgram = mpGraphics->CreateProgram(asName);
		
		lProgramList.push_back(pProgram);

		return pProgram;
	}

	iGpuProgram* cGraphics::CreateShaderProgram(const tString& asName, const tString& asPixShader, const tString& asVertShader)
	{
		iShader* pVertShader = mpResources->GetShaderManager()->CreateShader(asVertShader, eVertexShader);
		if (pVertShader == NULL) { Error("Failed to load vertex shader!\n"); return NULL; }
		Log("%d'\n", pVertShader);
		iShader* pPixShader = mpResources->GetShaderManager()->CreateShader(asPixShader, ePixelShader);
		if (pPixShader == NULL) { Error("Failed to load Fragment shader\n"); mpResources->GetShaderManager()->Delete(pVertShader); return NULL; }

		iGpuProgram* pProgram = CreateProgram(asName);
		pProgram->SetShader(pVertShader, eVertexShader);
		pProgram->SetShader(pPixShader, ePixelShader);
		pProgram->Link();
		pProgram->Bind();

		Log("Program '%s' successfully created!\n", asName.c_str());

		return pProgram;
	}








}