#pragma once

#include <IUnknownInterface.h>
#include <apiMessages.h>
#include <windows.h>

class AimpPlugin;

class AimpMessageHook : public IUnknownInterfaceImpl<IAIMPMessageHook>
{
	virtual void WINAPI CoreMessage(DWORD dwMessage, INT iParam, PVOID pParam, HRESULT *hResult);

public:
	AimpMessageHook(AimpPlugin *pPlugin);
	HRESULT Enable();
	HRESULT Disable();

private:
	AimpPlugin *pPlugin = NULL;
	IAIMPServiceMessageDispatcher *pMessageDispatcher = NULL;
};
