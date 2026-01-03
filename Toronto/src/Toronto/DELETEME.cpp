#include "InputTestDELETEWHENDONE.h"

cActionTest::cActionTest() : iUpdateable("TEST KILLIT")
{
	mpAction = gpBase->GetEngine()->GetInput()->CreateAction("Test Action");
	mpAction->AddKey(eKey_A);
	mpAction->AddControllerButton(eGamepadButton_0,0);

	gpBase->GetEngine()->GetInput()->CreateAction("TestMouseButton")->AddMouseButton(eMouseButton_Left);

	gpBase->GetEngine()->GetInput()->CreateAction("TestGamepadButton")->AddControllerButton(eGamepadButton_1,0);

	gpBase->GetEngine()->GetInput()->CreateAction("TestGamepadButton2")->AddControllerButton(eGamepadButton_3,0);
}

cActionTest::~cActionTest()
{
}

void cActionTest::OnUpdate(float afStep)
{
	int i = 1;
	if (gpBase->GetEngine()->GetInput()->BecameTriggered("Test Action"))
	{
		cDate Time = cPlatform::GetLocalTime();
		Log("Button Pushed at '%s %d'\n", Time.ToString().c_str(), cPlatform::GetAppTime());
		
		gpBase->GetEngine()->GetSystem()->TestString();
		gpBase->GetEngine()->GetGraphics()->CreateTempVtxBuffer(tVector3f(1) * i);
		gpBase->GetEngine()->GetGraphics()->SetClearColourTest(cMath::Rand(cColour(0,1), cColour(1,1)));
		i++;
		//cPlatform::ExecuteURL(L"https://pbs.twimg.com/media/E1IiCJPXoAI0DYP?format=jpg&name=large"); 
		gpBase->GetEngine()->GetInput()->GetGamepad(0)->RumbleController(0xFFFF, 0xFFFF, 1500);
	}

	if (gpBase->GetEngine()->GetInput()->BecameTriggered("TestMouseButton"))
	{
		//cPlatform::CreateMessageBox(eBoxTypeMessage, L"Chris Moltisanti Dies!!!", L"It's so sad man!!!");
	}

	if (gpBase->GetEngine()->GetInput()->BecameTriggered("TestGamepadButton"))
	{
		gpBase->GetEngine()->GetInput()->GetGamepad(0)->ChangeLEDColour(cMath::Rand(cColour(0, 0, 0, 0), cColour(255, 255, 255, 255)));
	}

	if (gpBase->GetEngine()->GetInput()->IsTriggered("TestGamepadButton2"))
	{
		gpBase->GetEngine()->GetInput()->GetGamepad(0)->RumbleController(0xFFFF, 0xFFFF, 1500);
	}
}