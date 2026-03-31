#include "BaseGame.h"



cOzyGameBase::cOzyGameBase()
{
	mpEngine = NULL;
}

cOzyGameBase::~cOzyGameBase()
{
	ExitEngine();
}

bool cOzyGameBase::Init(const tString &asCommandLine)
{
	if (!ParseCommandLine(asCommandLine)) return false;
	Log("%ls\n", cPlatform::GetCurrentWorkingDirectory());
	if (!InitEngine()) return false;
	if (!InitGame()) return false;

	return true;
}


void cOzyGameBase::Run()
{
	mpEngine->Run();
}

void cOzyGameBase::Exit()
{
	alkDelete(mpA);
}


void cOzyGameBase::ExitEngine()
{
	DestroyAlkaliEngine(mpEngine);
}




bool cOzyGameBase::ParseCommandLine(const tString& asCommandLine)
{
	if (asCommandLine == "-urltest")
	{
		cPlatform::ExecuteURL(L"https://www.youtube.com/watch?v=NxusabBT9ik");

		return true;
	}

	return true;
}


bool cOzyGameBase::InitGame()
{
	//@TODO: add this
	// temp for action testing
	cUpdater* pUpdater = GetEngine()->GetUpdater();
	pUpdater->AddAppContainer("TESTACTION",mpA);

	return true;
}

bool cOzyGameBase::InitEngine()
{
	mpEngine = CreateAlkaliEngine(eEngineInit_All, eEngineAPI_eOpenGl);
	mpA = alkNew(cActionTest, ());
	return true;
}