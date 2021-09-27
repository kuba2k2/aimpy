#pragma once

#include <windows.h>
#include <IUnknownInterface.h>
#include <apiPlugin.h>

#include "AimpMessageHook.h"
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
    IAIMPCore *pCore;
    AimpMessageHook *pHook = NULL;
    ServerThread *pServer = NULL;
};
