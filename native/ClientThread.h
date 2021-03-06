#pragma once

#include <windows.h>

#include "Thread.h"

class AimpPlugin;

class ClientThread : public Thread
{
	virtual DWORD Run();

public:
	ClientThread(AimpPlugin *pPlugin, HANDLE hPipe);
	BOOL Write(LPCVOID lpBuffer, DWORD szBuffer);

private:
	AimpPlugin *pPlugin = NULL;
	HANDLE hPipe;
};
