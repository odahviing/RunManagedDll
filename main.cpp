#pragma once
#include <windows.h>

using namespace System;
using namespace System::Reflection;
using namespace std;


//The entry point function for Rundll32 must be defined with the _stdcall calling convention (CALLBACK defaults to using the _stdcall attribute). 
//If the _stdcall attribute is missing, then the function defaults to _cdecl calling convention
//and then Rundll32 will terminate abnormally after calling the function.
//Since we must declare the function with _stdcall calling convention as described above,
//it follows that the Visual C++ compiler will actually export it as _Runt@16 for 32 bit build, for 64 bit it is done automatically by the linker

#ifndef _WIN64
#pragma comment(linker, "/EXPORT:Run=_Run@16")
#endif 


extern "C"
{
	__declspec(dllexport) BOOL CALLBACK Run(HWND /*hwnd*/, HINSTANCE /*hinst*/, LPSTR pszCmdLine, int /*nCmdShow*/)
	{
		String ^cmdLine = gcnew String(pszCmdLine);
		cli::array<String^>^ inputValues = cmdLine->Split(',');
		Assembly ^ dllHolder = Assembly::LoadFrom(inputValues[0]); //as rundll32 exact path is not required
		cli::array<Type^> ^allTypes = dllHolder->GetExportedTypes();

		for each (auto type in allTypes)
		{
			try
			{
				Console::WriteLine("Looking for method {0} in Class {1}", inputValues[1], type->FullName);
				type->InvokeMember(inputValues[1], BindingFlags::InvokeMethod, nullptr,
					Activator::CreateInstance(type), gcnew cli::array<Object^>{});
				Console::WriteLine("Found It! Finished running method {0} in Class {1}", inputValues[1], type->FullName);
				return TRUE;

			}
			catch (MissingMethodException^) {}
			catch (Exception^ e)
			{
				Console::WriteLine("Error: " + e->ToString());
				return FALSE;
			}
		}
		return FALSE;
	}
}

#pragma unmanaged

BOOL APIENTRY DllMain(HINSTANCE /*hinstDLL*/, DWORD fdwReason, LPVOID /*lpReserved*/)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

/* For Testing - Change to Debug*/
int main(int argc, CHAR* argv[])
{
	if (!argc)
		return -1;
	Run(NULL, NULL, argv[1], NULL);
	return 0;
}