#pragma once

#include <windows.h>

class AimpPlugin;

class PacketConsumer
{
public:
	PacketConsumer(AimpPlugin *pPlugin);

private:
	AimpPlugin *pPlugin = NULL;
};
