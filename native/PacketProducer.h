#pragma once

#include <windows.h>

class AimpPlugin;

class PacketProducer
{
public:
	PacketProducer(AimpPlugin *pPlugin);
	HRESULT ProduceFromMessage(DWORD dwMessage, INT iParam, PVOID pParam);

private:
	AimpPlugin *pPlugin = NULL;
};
