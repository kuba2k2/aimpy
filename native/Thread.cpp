#include "Thread.h"

HANDLE Thread::Start()
{
    this->hThread = CreateThread(
        NULL,
        0,
        this->ThreadEntryPoint,
        (LPVOID)this,
        0,
        &this->dwThreadId);
    return this->hThread;
}

BOOL Thread::Stop()
{
    return TerminateThread(this->hThread, -1);
}

DWORD WINAPI Thread::ThreadEntryPoint(LPVOID lpParam)
{
    return ((Thread *)lpParam)->Run();
}
