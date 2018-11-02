#pragma once
#include <windows.h>

using namespace System;
using namespace System::Reflection;
using namespace std;

extern "C"
{
	__declspec(dllexport) BOOL WINAPIV Run(HWND hwnd, HINSTANCE hinst, LPSTR pszCmdLine, int nCmdShow)
	{
		String ^cmdLine = gcnew String(pszCmdLine);
		cli::array<String^>^ inputValues = cmdLine->Split(',');
		Assembly ^ dllHolder = Assembly::LoadFile(inputValues[0]);
		cli::array<Type^> ^allTypes = dllHolder->GetExportedTypes();

		for (int i = 0; i < allTypes->Length; i++)
		{
			try
			{
				Console::WriteLine("Looking for method {0} in Class {1}", inputValues[1], allTypes[i]->FullName);
				allTypes[i]->InvokeMember(inputValues[1], BindingFlags::InvokeMethod, nullptr,
					Activator::CreateInstance(allTypes[i]), gcnew cli::array<Object^>{});
				Console::WriteLine("Found It! Finished running method {0} in Class {1}", inputValues[1], allTypes[i]->FullName);
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

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
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
int main(int argc, TCHAR* argv[])
{
	Run(NULL, NULL, argv[1], NULL);
	return 0;
}