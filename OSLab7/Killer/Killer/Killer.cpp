#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string>
#include <locale>
#include <codecvt>
#include <iostream>

std::wstring ctow(char* src)
{
    return std::wstring(src, src + strlen(src));
}

void killProccByName(std::wstring filename)
{
    PROCESSENTRY32 processEntry;
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    processEntry.dwSize = sizeof(processEntry);
    BOOL hRes = Process32First(hSnapShot, &processEntry);
    while (hRes)
    {
        if (processEntry.szExeFile == filename)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                (DWORD)processEntry.th32ProcessID);
            if (hProcess != NULL)
                TerminateProcess(hProcess, NULL);
        }
        hRes = Process32Next(hSnapShot, &processEntry);
    }
    CloseHandle(hSnapShot);
}

void killProccById(INT32 id)
{
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, id);
    TerminateProcess(hProcess, NULL);
}


int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        if (!strcmp(argv[i], "--name"))
            killProccByName(ctow(argv[i + 1]));
        if (!strcmp(argv[i], "--id"))
            killProccById(std::atoi(argv[i + 1]));
    }
    return 0;
}