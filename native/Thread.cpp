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
	BOOL fSuccess = TerminateThread(this->hThread, -1);
	CloseHandle(this->hThread);
	return fSuccess;
}

BOOL Thread::IsAlive()
{
	DWORD dwResult = WaitForSingleObject(this->hThread, 0);
	return dwResult != WAIT_OBJECT_0;
}

DWORD WINAPI Thread::ThreadEntryPoint(LPVOID lpParam)
{
	Thread *pThread = ((Thread *)lpParam);
	DWORD dwExitCode = pThread->Run();
	CloseHandle(pThread->hThread);
	return dwExitCode;
}
