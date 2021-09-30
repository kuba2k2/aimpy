#pragma once

#include <windows.h>

class Thread
{
	virtual DWORD Run() = 0;
	static DWORD WINAPI ThreadEntryPoint(LPVOID lpParam);

public:
	HANDLE Start();
	BOOL Stop();
	BOOL IsAlive();

private:
	HANDLE hThread;
	DWORD dwThreadId;
};
