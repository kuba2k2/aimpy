#include "AimpPlugin.h"

extern "C"
{
    __declspec(dllexport) BOOL WINAPI AIMPPluginGetHeader(IAIMPPlugin **Header)
    {
        *Header = new AimpPlugin();
        return true;
    }
}
