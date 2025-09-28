#include <stdio.h>
#include "engine/LogWriter.h"
#include "system/String.h"

#define UNICODE

#include <Windows.h>

#include "SDL3/SDL.h"

#include "system/MemoryManager.h"

extern int AlkaliMain(const alk::tString &asCommandLine);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	return AlkaliMain(lpCmdLine);
}

//int main(int argc, char* argv[])
//{
//	
//	return 0;
//}