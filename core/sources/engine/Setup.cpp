#ifdef ALK_PLATFORM_WINDOWS
#define UNICODE
#include "Windows.h"
#include "ShlObj.h"
#endif

#include "stdio.h"
#include <string>

#include "engine/EngineTypes.h"


//extern int AlkaliMain(alk::tString &asCommandLine);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	printf("I Ran\n");
	return 0;
}

int main(int argc, char* argv[])
{
	printf("I Exist! Welcome To Alkali! \n");
	alk::Log("I'm Alive! Welcome to Alkali\n");
	
	return 0;
}
