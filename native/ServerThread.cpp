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
        printf("Awaiting client connection on %s\n", this->lpszPipeName);
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
            printf("Client connected\n");

            ClientThread *thread = new ClientThread(this->pPlugin, hPipe);
            hThread = thread->Start();

            if (hThread == NULL)
            {
                printf("CreateThread failed, GLE=0x%04x\n", GetLastError());
                continue;
            }
            // else
            CloseHandle(hThread);
            continue;
        }
        // else
        CloseHandle(hPipe);
    }

    return 0;
}
