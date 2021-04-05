#include <stdio.h>
#include <stdint.h>
#include <combaseapi.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <Windows.h>

#include "coreclrhost.h"

class CoreCLRLoader
{
	private:
	std::string DynamicCLRRuntimePath;
	HMODULE LoadedCoreCLRRuntime;

	void* HostHandle;
	unsigned int DomainID;

	typedef char* (*EntryPointMethod_ptr)();

	coreclr_initialize_ptr InitialzeCoreCLR;
	coreclr_create_delegate_ptr CreateManagedDelegate;
	coreclr_shutdown_ptr ShutdownCoreCLR;

	bool InitializeCoreCLRRuntime(LPCSTR dllPathDirectory, LPCSTR dllName);
	void BuildTPAList(const char* directory, const char* extension, std::string& tpaList);

	public:
	static CoreCLRLoader* GetInstance();
	bool LoadCoreCLRRuntime(LPCSTR runtimeVersion, LPCSTR dllPathDirectory, LPCSTR dllName);
	bool UnloadCoreCLRRuntime();
	bool InvokeEntryPointMethod(LPCSTR dllNamespace, LPCSTR methodClass, LPCSTR methodName);
};