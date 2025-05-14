#include <stdio.h>
#include "engine/LogWriter.h"
#include "system/String.h"
#include <Windows.h>

#include "SDL3/SDL.h"


extern int AlkaliMain(const alk::tString &asCommandLine);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	
	return AlkaliMain(lpCmdLine);
}

//int main()
//{
//	
//	return 0;
//}