#pragma once

#include <windows.h>

#include "Thread.h"

class AimpPlugin;

class ServerThread : public Thread
{
	virtual DWORD Run();

public:
	ServerThread(AimpPlugin *pPlugin);

private:
	AimpPlugin *pPlugin = NULL;
	LPCTSTR lpszPipeName;
};
