#include <stdio.h>
#include "engine/LogWriter.h"
#include "system/String.h"

#define UNICODE

#include <Windows.h>



extern int AlkaliMain(const alk::tString &asCommandLine);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	return AlkaliMain(lpCmdLine);
}

//int main(int argc, char* argv[])
//{
//	
//	return 0;
//}