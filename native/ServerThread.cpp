#include "ServerThread.h"
#include "AimpPlugin.h"

#include <stdio.h>

#include "ClientThread.h"
#include "NamedPipeConst.h"

ServerThread::ServerThread(AimpPlugin *pPlugin)
{
	this->pPlugin = pPlugin;
	this->lpszPipeName = TEXT(PIPE_NAME);
}

DWORD ServerThread::Run()
{
	printf("ServerThread::Run()\n");

	BOOL fConnected = FALSE;
	HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;

	for (;;)
	{
		printf("[Server] Awaiting client connection on %s\n", this->lpszPipeName);
		hPipe = CreateNamedPipe(
			this->lpszPipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			PIPE_BUFSIZE,
			PIPE_BUFSIZE,
			NMPWAIT_USE_DEFAULT_WAIT, NULL);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			printf("CreateNamedPipe failed, GLE=0x%04x\n", GetLastError());
			break;
		}

		fConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (fConnected)
		{
			printf("[Server] Client connected\n");

			ClientThread *client = new ClientThread(this->pPlugin, hPipe);
			hThread = client->Start();
			// this->vClients.push_back(*client);
			this->vClients.emplace_back(*client);

			if (hThread == NULL)
			{
				printf("CreateThread failed, GLE=0x%04x\n", GetLastError());
				continue;
			}
			// else
			continue;
		}
		// else
		CloseHandle(hPipe);
	}

	return 0;
}

void ServerThread::Broadcast(LPCVOID lpBuffer, DWORD szBuffer)
{
	for (auto client = this->vClients.begin(); client != this->vClients.end();)
	{
		if (!client->IsAlive())
		{
			printf("[Broadcast] Thread terminated, erasing\n");
			this->vClients.erase(client);
			continue;
		}

		if (!client->Write(lpBuffer, szBuffer))
		{
			printf("[Broadcast] Thread write failed, erasing\n");
			this->vClients.erase(client);
			continue;
		}

		++client;
	}
}
