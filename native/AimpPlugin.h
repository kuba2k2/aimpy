#pragma once

#include <IUnknownInterface.h>
#include <tchar.h>
#include <windows.h>

#include <apiPlayer.h>
#include <apiPlugin.h>

#include "AimpMessageHook.h"
#include "PacketConsumer.h"
#include "PacketProducer.h"
#include "ServerThread.h"

class AimpPlugin : public IUnknownInterfaceImpl<IAIMPPlugin>
{
	// Information about the plugin
	virtual PWCHAR WINAPI InfoGet(int Index);
	virtual DWORD WINAPI InfoGetCategories();
	// Initialization / Finalization
	virtual HRESULT WINAPI Initialize(IAIMPCore *Core);
	virtual HRESULT WINAPI Finalize();
	// System Notifications
	virtual void WINAPI SystemNotification(int NotifyID, IUnknown *Data);

public:
	IAIMPCore *pCore = NULL;
	IAIMPServicePlayer *pPlayer = NULL;
	IAIMPServiceVersionInfo *pVersionInfo = NULL;

	AimpMessageHook *pHook = NULL;
	PacketConsumer *pConsumer = NULL;
	PacketProducer *pProducer = NULL;
	ServerThread *pServer = NULL;
};
