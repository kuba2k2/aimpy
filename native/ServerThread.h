#pragma once

#include <vector>
#include <windows.h>

#include "ClientThread.h"
#include "Thread.h"

class AimpPlugin;

class ServerThread : public Thread
{
	virtual DWORD Run();

public:
	ServerThread(AimpPlugin *pPlugin);
	void Broadcast(LPCVOID lpBuffer, DWORD szBuffer);

private:
	AimpPlugin *pPlugin = NULL;
	std::vector<ClientThread> vClients;
	LPCTSTR lpszPipeName;
};
