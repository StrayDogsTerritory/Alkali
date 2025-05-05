#include <stdio.h>
#include "engine/LogWriter.h"
#include "system/String.h"
#include <Windows.h>

extern int AlkaliMain(const alk::tString &asCommandLine);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return AlkaliMain(lpCmdLine);
}

int main(int argc, char* argv[])
{
	alk::Log("This is a Normal Message!\n");
	alk::Log("This is a Warning Message!\n", alk::eMessageType::eTypeWarning);
	alk::Log("This is a Normal Message!\n", alk::eMessageType::eTypeWarning);
	alk::Log("This is a Normal Message!\n", alk::eMessageType::eTypeWarning);

	return 0;
}