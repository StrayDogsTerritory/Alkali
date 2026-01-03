#include "BaseGame.h"



cTorGameBase::cTorGameBase()
{
	mpEngine = NULL;
}

cTorGameBase::~cTorGameBase()
{
	ExitEngine();
}

bool cTorGameBase::Init(const tString &asCommandLine)
{
	if (!ParseCommandLine(asCommandLine)) return false;
	if (!InitEngine()) return false;
	if (!InitGame()) return false;

	return true;
}


void cTorGameBase::Run()
{
	mpEngine->Run();
}

void cTorGameBase::Exit()
{
	alkDelete(mpA);
}


void cTorGameBase::ExitEngine()
{
	DestroyAlkaliEngine(mpEngine);
}




bool cTorGameBase::ParseCommandLine(const tString& asCommandLine)
{
	if (asCommandLine == "-urltest")
	{
		cPlatform::ExecuteURL(L"https://www.youtube.com/watch?v=NxusabBT9ik");

		return true;
	}

	return true;
}


bool cTorGameBase::InitGame()
{
	//@TODO: add this
	// temp for action testing
	cUpdater* pUpdater = GetEngine()->GetUpdater();
	pUpdater->AddAppContainer("TESTACTION",mpA);

	return true;
}

bool cTorGameBase::InitEngine()
{
	mpEngine = CreateAlkaliEngine(eEngineInit_All, eEngineAPI_eOpenGl);
	mpA = alkNew(cActionTest, ());
	return true;
}