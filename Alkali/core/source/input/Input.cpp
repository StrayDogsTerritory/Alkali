#include "input/Input.h"
#include "input/InputInterface.h"
//#include "SDL3/SDL.h"
#include "engine/LogWriter.h"

namespace alk {

	cInput::cInput(iInput* apInputInterfaec) : iUpdateable("Input")
	{
		mpInput = apInputInterfaec;
		mbQuitting = false;
	}

	cInput::~cInput()
	{
	}

	void cInput::OnUpdate(float afStep)
	{
		mpInput->Update(afStep);
	}

	bool cInput::GetIsQuit()
	{
		return mpInput->GetIsQuit();
	}

	void cInput::ProcessEvent()
	{
		
	}

}