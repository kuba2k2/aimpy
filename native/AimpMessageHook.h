#pragma once

#include <IUnknownInterface.h>
#include <apiMessages.h>
#include <windows.h>

class AimpPlugin;

class AimpMessageHook : public IUnknownInterfaceImpl<IAIMPMessageHook>
{
	virtual void WINAPI CoreMessage(DWORD dwMessage, int iParam1, void *pParam2, HRESULT *hResult);

public:
	AimpMessageHook(AimpPlugin *pPlugin);
	HRESULT Enable();
	HRESULT Disable();

private:
	AimpPlugin *pPlugin = NULL;
	IAIMPServiceMessageDispatcher *pMessageDispatcher = NULL;
};
