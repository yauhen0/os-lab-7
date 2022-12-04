#include <iostream>
#include <windows.h>
#include <vector>
#include <stdlib.h>

std::wstring stow(const std::string& str)
{
	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], sizeNeeded);
	return wstrTo;
}

std::wstring createCMD(const std::vector<std::wstring>& args)
{
	std::wstring cmd = L"..\\..\\..\\Killer\\x64\\Debug\\Killer.exe";

	for (auto& arg : args)
	{
		cmd += L" " + std::wstring(arg.begin(), arg.end());
	}
	return cmd;
}

void callKiller(std::wstring str)
{
	PROCESS_INFORMATION processInfo;
	STARTUPINFO  startInfo;
	ZeroMemory(&startInfo, sizeof(startInfo));
	ZeroMemory(&processInfo, sizeof(processInfo));
	CreateProcess(NULL, &str.front(), NULL, NULL, TRUE, 0, NULL, NULL, &startInfo, &processInfo);
	WaitForSingleObject(processInfo.hProcess, INFINITE);
}

int main(int argc, char* argv[])
{

	std::vector<std::wstring> args;
	for (int i = 1; i < argc; ++i)
		args.push_back(stow(argv[i]));

	std::wstring cl = createCMD(args);
	callKiller(cl);

}