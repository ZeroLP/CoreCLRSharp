// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "CoreCLRLoader.h"

void _stdcall StartRuntime()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    bool ldrStat = CoreCLRLoader::GetInstance()->LoadCoreCLRRuntime("5.0.0", "PATH\\TO\\CoreCLR.NET5\\bin\\Debug\\net5.0",
                                                                    "CoreCLR.NET5.dll");

    if (ldrStat)
    {
        if (CoreCLRLoader::GetInstance()->InvokeEntryPointMethod("CoreCLR.NET5", "CoreCLR.NET5.EntryPoint", "Main"))
            printf("Successfully invoked entrypoint method.\n");
        else
            printf("Failed to invoked entrypoint method.\n");
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartRuntime, 0, 0, 0);
            return true;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

