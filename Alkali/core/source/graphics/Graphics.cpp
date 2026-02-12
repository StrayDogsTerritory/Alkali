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
#include "graphics/Bitmap.h"
#include "graphics/Texture.h"

#include "resources/Resources.h"
#include "resources/ResourceManager.h"
#include "resources/ShaderManager.h"
#include "resources/Filesearcher.h"
#include "resources/BitmapLoader.h" // @TODO: make this the texture manager 

#include "math/Vector2.h"
#include "math/Vector3.h"

#include <IL/il.h>

namespace alk {

	cGraphics::cGraphics(iGraphics* apGraphics) : iUpdateable("Graphics")
	{	
		mpResources = NULL;
		mpGraphics = apGraphics;

		mbCreatedProgram = false;
		mpTestProgram = NULL;
	}

	cGraphics::~cGraphics()
	{
		Log("---------------------------------------------\n");
		Log("Quitting graphics module\n");

		Log("deleting module created programs\n");
		DeleteAll(lProgramList);
		Log("deleting module created vertex buffers\n");
		DeleteAll(lVtxBuffList);

		alkDelete(mpTestTexture);

		Log("---------------------------------------------\n\n");
	}

	bool cGraphics::Init(cResources* apResources, int alHeight, int alWidth, int alWindowMode)
	{
		Log("---------------------------------------------\n");
		mpResources = apResources;
		mpGraphics->Init(alHeight, alWidth, alWindowMode);

		
		mpResources->AddDirectory(L"test/shaders", true);

		Log("---------------------------------------------\n");


		cBitmap* pBitmap = mpResources->GetBitmapLoader()->LoadBitmap(L"test/photomode_03072025_150327.png");
		mpTestTexture = mpGraphics->CreateTexture("aTex_Diffuse");
		mpTestTexture->CreateTextureFromBitmap(pBitmap->GetDimensions(), pBitmap);
		alkDelete(pBitmap);

		return true;
	}

	void cGraphics::OnUpdate(float afStep)
	{
	//	Log("VtxBuff size: '%d'\n", lVtxBuffList.size());

		
		if (mbCreatedProgram == false)
		{
			mbCreatedProgram = true;
			//Log("Created Program. Should only be seen once!\n");
			//Log("Program list size: '%d'", lProgramList.size());
			mpTestProgram = CreateShaderProgram("TestProgram", "test_frag.glsl", "test_vert.glsl");
			
		}

		//CreateTempVtxBuffer(1);

		

		for (tVtxBuffListIt it = lVtxBuffList.begin(); it != lVtxBuffList.end(); ++it)
		{
			iVertexBuffer* pBuff = (*it);
			
			//mpTestProgram->SetInt(0, 0);

			mpTestTexture->Bind(0);

			mpTestProgram->Bind();

			pBuff->Bind();
			pBuff->Draw();
			pBuff->UnBind();

			//mpTestProgram->UnBind();
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
		iShader* pVertShader = mpResources->GetShaderManager()->CreateShader(asVertShader, eShaderType_eVertexShader);
		if (pVertShader == NULL) { Error("Failed to load vertex shader!\n"); return NULL; }
		iShader* pPixShader = mpResources->GetShaderManager()->CreateShader(asPixShader, eShaderType_ePixelShader);
		if (pPixShader == NULL) { Error("Failed to load Fragment shader\n"); mpResources->GetShaderManager()->Delete(pVertShader); return NULL; }

		iGpuProgram* pProgram = CreateProgram(asName);
		pProgram->SetShader(pVertShader, eShaderType_eVertexShader);
		pProgram->SetShader(pPixShader, eShaderType_ePixelShader);
		pProgram->Link();
		pProgram->Bind();

	//	Log("Program '%s' successfully created!\n", asName.c_str());

		return pProgram;
	}

	static tVector3f GetBoxTex(int i, int x, int y, int z, tVector3f* vAdd)
	{
		tVector3f vTex;

		if (std::abs(x)) {
			vTex.x = vAdd[i].z;
			vTex.y = vAdd[i].y;
		}
		else if (std::abs(y)) {
			vTex.x = vAdd[i].x;
			vTex.y = vAdd[i].z;
		}
		else if (std::abs(z)) {
			vTex.x = vAdd[i].x;
			vTex.y = vAdd[i].y;
		}

		//Inverse for negative directions
		if (x + y + z < 0)
		{
			vTex.x = -vTex.x;
			vTex.y = -vTex.y;
		}

		return vTex;
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


		iVertexBuffer* pBox = mpGraphics->CreateVertexBuffer(eDrawtype_Static,ePrimitiveAssemblyType_Tri);
		pBox->CreateElementArray(eElementArrayType_Position, eArrayFormat_Float, 4);
		pBox->CreateElementArray(eElementArrayType_Normals, eArrayFormat_Float, 3);
		pBox->CreateElementArray(eElementArrayType_Colour, eArrayFormat_Float, 4);
		pBox->CreateElementArray(eElementArrayType_Texture, eArrayFormat_Float, 3);

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
						tVector3f vTex = GetBoxTex(i, x, y, z, vAdd);

						//pBox->AddVertexColour(eElementArrayType_Colour, cMath::Rand(cColour(0,0,0,0),cColour(1,1,1,1)));
						pBox->AddVertexColour(eElementArrayType_Colour,cColour(1,1,1,1));
						pBox->AddVertex(eElementArrayType_Position, (vDir + vAdd[idx]) * avSize);
						pBox->AddVertex(eElementArrayType_Normals, vDir);

						tVector3f vCoord = tVector3f((vTex.x + 1) * 0.5f, (vTex.y + 1) * 0.5f, 0);
						pBox->AddVertex(eElementArrayType_Texture, vCoord);

						vSide = vDir + vAdd[idx];
						
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

		DeleteAll(lVtxBuffList);
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