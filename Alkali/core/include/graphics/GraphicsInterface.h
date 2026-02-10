#ifndef ALK_GRAPHICSINTERFACE_H
#define ALK_GRAPHICSINTERFACE_H


#include "system/FlagBits.h"
#include "system/String.h"

#include "graphics/Shader.h"
#include "graphics/VertexBuffer.h"

enum eGpuMaximum
{
	eGpuMaximum_3DTextureSize,
	eGpuMaximum_ArrayTextureLayers,
	eGpuMaximum_ClipDistances,
	eGpuMaximum_ColourTextureSamples,
	eGpuMaximum_CombinedFragmentUniformComponents,
	eGpuMaximum_CombinedVertexUniformComponents,
	eGpuMaximum_CombinedTextureImageUnits,
	eGpuMaximum_TextureBufferSize,
	eGpuMaximum_TextureImageUnits,
	eGpuMaximum_TextureLODBias,
	eGpuMaximum_TextureSize,
	eGpuMaximum_VertexAttribs,
	eGpuMaximum_NumViewports,
};

namespace alk {

	class iShader;
	class iGpuProgram;
	class cColour;
	class iVertexBuffer;
	class iTexture;

	class iGraphics
	{
	public:
		virtual ~iGraphics() {};
		virtual bool Init(int alHeight, int alWidth, int alWindowMode) = 0;

		virtual int GetCardMaxes(eGpuMaximum aGpuMaxes)=0;

		virtual iShader* CreateShader(const tString& asName, eShaderType aType)=0;
		virtual iGpuProgram* CreateProgram(const tString& asName)=0;
		virtual iVertexBuffer* CreateVertexBuffer(eVertexBufferDrawType aDrawType, eVertexBufferPrimitiveAssemblyType aPrimAssemblyType)=0;
		virtual iTexture* CreateTexture(const tString& asName)=0;

		virtual void SwapBuffer()=0;
		virtual bool SetCursorVisibility(bool abx) = 0;
		virtual bool SetWindowFullscreen(bool abx) = 0;
		virtual bool SetWindowBorderless(bool abx) = 0;
		virtual bool SetWindowGrabInput(bool abx) = 0;
		virtual void SetClearColour(const cColour& aColR) = 0;
		virtual void ClearFrameBuffer(tFlag aClearFlag)=0;
		virtual void FlushRender()=0;
		virtual void SetVSync(bool abx)=0; // fill this later
		virtual void SetRelativeMouse(bool abx)=0;
	};

}
#endif
