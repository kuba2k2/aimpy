#include "AimpPlugin.h"

#include <apiMessages.h>
#include <stdio.h>

#include "Console.h"
#include "addressbook.pb.h"

using namespace tutorial;

PWCHAR WINAPI AimpPlugin::InfoGet(int Index)
{
	switch (Index)
	{
		case AIMP_PLUGIN_INFO_NAME:
			return const_cast<PWCHAR>(L"aimpy");
		case AIMP_PLUGIN_INFO_AUTHOR:
			return const_cast<PWCHAR>(L"kuba2k2");
		case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
			return const_cast<PWCHAR>(L"aimpy IPC plugin");
	}

	return NULL;
}

DWORD WINAPI AimpPlugin::InfoGetCategories()
{
	return AIMP_PLUGIN_CATEGORY_ADDONS;
}

HRESULT WINAPI AimpPlugin::Initialize(IAIMPCore *Core)
{
	EnableConsoleWindow();

	this->pCore = Core;
	Core->QueryInterface(IID_IAIMPServicePlayer, (void **)&this->pPlayer);
	Core->QueryInterface(IID_IAIMPServiceVersionInfo, (void **)&this->pVersionInfo);

	// if (this->pHook == NULL)
	this->pHook = new AimpMessageHook(this);

	// if (this->pConsumer == NULL)
	this->pConsumer = new PacketConsumer(this);

	// if (this->pProducer == NULL)
	this->pProducer = new PacketProducer(this);

	// if (this->pServer == NULL)
	this->pServer = new ServerThread(this);

	IAIMPString *asVersion;
	this->pVersionInfo->FormatInfo(&asVersion);
	PWCHAR pwszVersion = asVersion->GetData();

	printf("Running on AIMP %ls\n", pwszVersion);

	this->pServer->Start();
	this->pHook->Enable();

	printf("OK\n");

	return S_OK;
}

HRESULT WINAPI AimpPlugin::Finalize()
{
	if (this->pHook != NULL)
		this->pHook->Disable();
	if (this->pServer != NULL)
		this->pServer->Stop();
	return S_OK;
}

void WINAPI AimpPlugin::SystemNotification(int NotifyID, IUnknown *Data)
{
}
