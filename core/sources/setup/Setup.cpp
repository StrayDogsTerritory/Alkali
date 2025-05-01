#ifdef ALK_PLATFORM_WINDOWS
#define UNICODE
#include "Windows.h"
#include "ShlObj.h"
#endif

#include "stdio.h"
#include <string>

#ifndef IGNORE_ALK_MAIN

#ifdef ALK_PLATFORM_WINDOWS
extern int AlkaliMain(std::string &asCommandLine);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	printf("I Ran\n");
	return 0;
}


int main()
{
	printf("I Exist! Welcome To Alkali! \n");
	return 0;
}
#endif 


#endif