#include "graphics/Graphics.h"
#include "system/MemoryManager.h"
#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "graphics/GPUProgram.h"
#include "graphics/GPUProgramGLSL.h"
#include "engine/LogWriter.h"
#include "system/String.h"

#include "graphics/Colour.h"
#include "graphics/GraphicsInterface.h"
#include "graphics/VertexBufferGL.h"
#include "graphics/VertexBuffer.h"

#include "resources/Resources.h"
#include "resources/ResourceManager.h"
#include "resources/ShaderManager.h"
#include "resources/Filesearcher.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace alk {

	cGraphics::cGraphics(iGraphics* apGraphics) : iUpdateable("Graphics")
	{	
		mpResources = NULL;
		mpGraphics = apGraphics;

	}

	cGraphics::~cGraphics()
	{
		Log("Beginning cGraphics Destructor\n");

		DeleteAll(lProgramList);
		DeleteAll(lVtxBuffList);

		Log("Ending cGraphics Destructor\n");
	}

	bool cGraphics::Init(cResources* apResources, int alHeight, int alWidth, int alWindowMode)
	{
		mpResources = apResources;
		mpGraphics->Init(alHeight, alWidth, alWindowMode);

		
		mpResources->AddDirectory(L"test/shaders", true);

		//iVertexBuffer* pVtxBuffer = CreateTempVtxBuffer(tVector3f(1,1,1));
		//pVtxBuffer->Compile();
		
		//mpGraphics->SwapBuffer();
		
		//CreateShaderProgram("testProgram", "test_frag.glsl", "test_vert.glsl");

		
		return true;
	}

	void cGraphics::OnUpdate(float afStep)
	{
		Log("VtxBuff size: '%d'\n", lVtxBuffList.size());
		for (tVtxBuffListIt it = lVtxBuffList.begin(); it != lVtxBuffList.end(); ++it)
		{
			iVertexBuffer* pBuff = (*it);
			pBuff->Bind();
			pBuff->Draw();
		}
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

	iVertexBuffer* cGraphics::CreateTempVtxBuffer(tVector3f avSize)
	{
		/*tVector3f vVerts[3] = { tVector3f(-0.5,-0.5,-0.5), tVector3f(0.5,-0.5,-0.5), tVector3f(0.5,-0.5,0.5)};
		tVector3f vNorm[3] = { tVector3f(-1.0,0.0,0.0), tVector3f(0.0, 0.0,-1.0), tVector3f(0.0,1.0,0.0) };
		cColour Col(1, 1, 1, 1);

		iVertexBuffer* pTri = mpGraphics->CreateVertexBuffer();
		pTri->CreateElementArray(eElementArrayType_Position, eArrayFormat_Float, 4);
		pTri->CreateElementArray(eElementArrayType_Normals, eArrayFormat_Float, 3);
		pTri->CreateElementArray(eElementArrayType_Colour, eArrayFormat_Float, 4);

		for (int i = 0; i < 2; i++)
		{
			pTri->AddVertex(eElementArrayType_Position, vVerts[i]);
			pTri->AddVertex(eElementArrayType_Normals, vNorm[i]);
			pTri->AddVertexColour(eElementArrayType_Colour, Col);
		}*/


		iVertexBuffer* pBox = mpGraphics->CreateVertexBuffer();
		pBox->CreateElementArray(eElementArrayType_Position, eArrayFormat_Float, 4);
		pBox->CreateElementArray(eElementArrayType_Normals, eArrayFormat_Float, 3);
		pBox->CreateElementArray(eElementArrayType_Colour, eArrayFormat_Float, 4);

		avSize = avSize * 0.5;


		int lVtxIdx = 0;

		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
				for (int z = -1; z <= 1; z++)
				{
					if (x == 0 && y == 0 && z == 0)continue;
					if (std::abs(x) + std::abs(y) + std::abs(z) > 1)continue;

					//Direction (could say inverse normal) of the quad.
					tVector3f vDir(0);
					tVector3f vSide(0);

					tVector3f vAdd[4];
					if (std::abs(x)) {
						vDir.x = (float)x;

						vAdd[0].y = 1;	vAdd[0].z = 1;	vAdd[0].x = 0;
						vAdd[1].y = -1;	vAdd[1].z = 1;	vAdd[1].x = 0;
						vAdd[2].y = -1;	vAdd[2].z = -1;	vAdd[2].x = 0;
						vAdd[3].y = 1;	vAdd[3].z = -1;	vAdd[3].x = 0;
					}
					else if (std::abs(y)) {
						vDir.y = (float)y;

						vAdd[0].z = 1;	vAdd[0].x = 1;	vAdd[0].y = 0;
						vAdd[1].z = -1;	vAdd[1].x = 1;	vAdd[1].y = 0;
						vAdd[2].z = -1;	vAdd[2].x = -1;	vAdd[2].y = 0;
						vAdd[3].z = 1;	vAdd[3].x = -1;	vAdd[3].y = 0;
					}
					else if (std::abs(z)) {
						vAdd[0].y = 1;	vAdd[0].x = 1;	vAdd[0].z = 0;
						vAdd[1].y = 1;	vAdd[1].x = -1;	vAdd[1].z = 0;
						vAdd[2].y = -1;	vAdd[2].x = -1;	vAdd[2].z = 0;
						vAdd[3].y = -1;	vAdd[3].x = 1;	vAdd[3].z = 0;

						vDir.z = (float)z;
					}


					//Log("Side: (%.0f : %.0f : %.0f) [ ", vDir.x,  vDir.y,vDir.z);
					for (int i = 0; i < 4; i++)
					{
						int idx = GetBoxIdx(i, x, y, z);
						//tVector3f vTex = GetBoxTex(i, x, y, z, vAdd);

						pBox->AddVertexColour(eElementArrayType_Colour, cMath::Rand(cColour(0,0,0,0),cColour(1,1,1,1)));
						pBox->AddVertex(eElementArrayType_Position, (vDir + vAdd[idx]) * avSize);
						pBox->AddVertex(eElementArrayType_Normals, vDir);

						vSide = vDir + vAdd[idx];
						//Log("%d: Tex: (%.1f : %.1f : %.1f) ", i,vTex.x,  vTex.y,vTex.z);
						//Log("%d: (%.1f : %.1f : %.1f) ", i,vSide.x,  vSide.y,vSide.z);
					}

					for (int i = 0; i < 3; i++)
						pBox->AddIndex(lVtxIdx + i);
					pBox->AddIndex(lVtxIdx + 2);
					pBox->AddIndex(lVtxIdx + 3);
					pBox->AddIndex(lVtxIdx + 0);

					lVtxIdx += 4;

					//Log("\n");
				}

		pBox->Compile();

		lVtxBuffList.push_back(pBox);

		return pBox;
	}

		
	

	int cGraphics::GetBoxIdx(int i, int x, int y, int z)
	{
		int idx = i;
		if (x + y + z > 0) idx = 3 - i;

		return idx;
	}

	void cGraphics::SetClearColourTest(cColour aCol)
	{
		mpGraphics->SetClearColour(aCol);
		//mpGraphics->ClearFrameBuffer(0);
	}
}