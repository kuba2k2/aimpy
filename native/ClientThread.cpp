#include "ClientThread.h"
#include "AimpPlugin.h"

#include <stdio.h>

#include "NamedPipeConst.h"

ClientThread::ClientThread(AimpPlugin *pPlugin, HANDLE hPipe)
{
	this->pPlugin = pPlugin;
	this->hPipe = hPipe;
}

DWORD ClientThread::Run()
{
	printf("ClientThread::Run()\n");

	HANDLE hHeap = GetProcessHeap();
	TCHAR *pchRequest = (TCHAR *)HeapAlloc(hHeap, 0, PIPE_BUFSIZE * sizeof(TCHAR));
	TCHAR *pchReply = (TCHAR *)HeapAlloc(hHeap, 0, PIPE_BUFSIZE * sizeof(TCHAR));

	DWORD cbReplyBytes = 0, cbWritten = 0;
	BOOL fSuccess = FALSE;

	sprintf(pchReply, "Hello From ClientThread\n");
	cbReplyBytes = strlen(pchReply);

	for (;;)
	{
		if (!this->Write(pchReply, cbReplyBytes))
			break;
		Sleep(1000);
	}

	printf("ClientThread exiting...\n");

	FlushFileBuffers(this->hPipe);
	DisconnectNamedPipe(this->hPipe);
	CloseHandle(this->hPipe);
	HeapFree(hHeap, 0, pchRequest);
	HeapFree(hHeap, 0, pchReply);

	return 0;
}

BOOL ClientThread::Write(LPCVOID lpBuffer, DWORD szBuffer)
{
	DWORD cbWritten = 0;
	BOOL fSuccess = WriteFile(
		this->hPipe,
		lpBuffer,
		szBuffer,
		&cbWritten,
		NULL);

	return fSuccess && cbWritten == szBuffer;
}
