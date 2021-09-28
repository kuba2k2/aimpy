#include "AimpMessageHook.h"
#include "AimpPlugin.h"

#include <stdio.h>

AimpMessageHook::AimpMessageHook(AimpPlugin *pPlugin)
{
	this->pPlugin = pPlugin;

	if (this->pMessageDispatcher == NULL)
	{
		this->pPlugin->pCore->QueryInterface(IID_IAIMPServiceMessageDispatcher, (void **)&this->pMessageDispatcher);
	}
}

HRESULT AimpMessageHook::Enable()
{
	return this->pMessageDispatcher->Hook(this);
}

HRESULT AimpMessageHook::Disable()
{
	return this->pMessageDispatcher->Unhook(this);
}

void WINAPI AimpMessageHook::CoreMessage(DWORD dwMessage, int iParam1, void *pParam2, HRESULT *hResult)
{
	float fPosition = 0.0;

	switch (dwMessage)
	{
		case AIMP_MSG_EVENT_PLAYER_UPDATE_POSITION:
			printf("Position changed ?\n");
			this->pMessageDispatcher->Send(AIMP_MSG_PROPERTY_PLAYER_POSITION, AIMP_MSG_PROPVALUE_GET, NULL);
			break;
		case AIMP_MSG_EVENT_PROPERTY_VALUE:
			switch (iParam1)
			{
				case AIMP_MSG_PROPERTY_PLAYER_POSITION:
					fPosition = *((float *)pParam2);
					printf("Seek event to: %f s\n", fPosition);
					break;
				default:
					printf("CoreMessage(AIMP_MSG_EVENT_PROPERTY_VALUE, %d, ...)\n", iParam1);
					break;
			}
			break;
		default:
			// printf("CoreMessage(%d, %d, ...)\n", dwMessage, iParam1);
			break;
	}
}
