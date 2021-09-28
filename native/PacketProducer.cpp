#include "PacketProducer.h"
#include "AimpPlugin.h"

#include <stdio.h>

PacketProducer::PacketProducer(AimpPlugin *pPlugin)
{
	this->pPlugin = pPlugin;
}

HRESULT PacketProducer::ProduceFromMessage(DWORD dwMessage, INT iParam, PVOID pParam)
{
	switch (dwMessage)
	{
		case AIMP_MSG_EVENT_PLAYER_UPDATE_POSITION_HR:
			double fpPosition = 0.0;
			this->pPlugin->pPlayer->GetPosition(&fpPosition);
			printf("Current position: %.2f\n", fpPosition);
			break;
	}

	return S_OK;
}
