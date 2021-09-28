#include "AimpMessageHook.h"
#include "AimpPlugin.h"

#include <stdio.h>

AimpMessageHook::AimpMessageHook(AimpPlugin *pPlugin)
{
	this->pPlugin = pPlugin;

	// if (this->pMessageDispatcher == NULL)
	// {
	this->pPlugin->pCore->QueryInterface(IID_IAIMPServiceMessageDispatcher, (void **)&this->pMessageDispatcher);
	// }
}

HRESULT AimpMessageHook::Enable()
{
	return this->pMessageDispatcher->Hook(this);
}

HRESULT AimpMessageHook::Disable()
{
	return this->pMessageDispatcher->Unhook(this);
}

void WINAPI AimpMessageHook::CoreMessage(DWORD dwMessage, INT iParam, PVOID pParam, HRESULT *hResult)
{
	/* *hResult = */ this->pPlugin->pProducer->ProduceFromMessage(dwMessage, iParam, pParam);
}
