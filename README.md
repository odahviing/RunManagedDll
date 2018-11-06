# run-managed-dll
Small utility to invoke managed DLL function via rundll32

With this utility you can run any managed dll functions without the need of altering the managed code.
The synatx is:

64bit
rundll32.exe managed64.dll,Run [Managed Dll Path],[Managed Function]
32bit
rundll32.exe managed32.dll,Run [Managed Dll Path],[Managed Function]

After building the solution for both platform (x86 and x64), you can test the basic functionality with:

for a 64 bit computer:

cd <Release Folder> 
rundll32 managed64.dll,Run LoadMe.dll,HelloWorld1
rundll32 managed64.dll,Run LoadMe.dll,HelloWorld2
%windir%\SysWOW64\rundll32 managed32.dll,Run LoadMe.dll,HelloWorld1
%windir%\SysWOW64\rundll32 managed32.dll,Run LoadMe.dll,HelloWorld2

for a 32 bit computer:

cd <Release Folder> 
rundll32 managed32.dll,Run LoadMe.dll,HelloWorld1
rundll32 managed32.dll,Run LoadMe.dll,HelloWorld2





