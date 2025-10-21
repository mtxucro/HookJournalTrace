#include <Windows.h>
#include <winioctl.h>
#include <string>
#include <vector>
#include <algorithm>
#include "MinHook.h"


using DeviceIoControlFn = BOOL(WINAPI*)(HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

DeviceIoControlFn g_OriginalDeviceIoControl = nullptr;

const std::vector<std::wstring> kBlockedFileNames = {
    L"malware.exe",
    L"unauthorized_access.exe",
    L".dll",
};

bool IsFileNameBlocked(const std::wstring& fileName) {
    return std::any_of(kBlockedFileNames.begin(), kBlockedFileNames.end(),
        [&fileName](const std::wstring& blocked) {
            return fileName.find(blocked) != std::wstring::npos;
        });
}

BOOL WINAPI DeviceIoControlHook(
    HANDLE hDevice,
    DWORD dwIoControlCode, 
    LPVOID lpInBuffer,
    DWORD nInBufferSize,
    LPVOID lpOutBuffer,
    DWORD nOutBufferSize,
    LPDWORD lpBytesReturned,
    LPOVERLAPPED lpOverlapped)
{
    BOOL result = g_OriginalDeviceIoControl(
        hDevice, dwIoControlCode, lpInBuffer, nInBufferSize,
        lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);

    if (result && dwIoControlCode == FSCTL_READ_USN_JOURNAL && lpOutBuffer && lpBytesReturned && *lpBytesReturned > 0) {
        BYTE* buffer = static_cast<BYTE*>(lpOutBuffer);
        DWORD totalSize = *lpBytesReturned;
        DWORD offset = 0;
        while (offset < totalSize) {
            auto* record = reinterpret_cast<USN_RECORD*>(buffer + offset);
            std::wstring fileName(record->FileName, record->FileNameLength / sizeof(WCHAR));
            if (IsFileNameBlocked(fileName)) {
                DWORD moveSize = totalSize - (offset + record->RecordLength);
                if (moveSize > 0) {
                    memmove(buffer + offset, buffer + offset + record->RecordLength, moveSize);
                }
                totalSize -= record->RecordLength;
                *lpBytesReturned -= record->RecordLength;
            } else {
                offset += record->RecordLength;
            }
        }
    }
    return result;
}

DWORD WINAPI InitializeDeviceIoControlHook(LPVOID) {
    if (MH_Initialize() != MH_OK) return 1;
    if (MH_CreateHook(&DeviceIoControl, &DeviceIoControlHook, reinterpret_cast<LPVOID*>(&g_OriginalDeviceIoControl)) != MH_OK) return 1;
    if (MH_EnableHook(&DeviceIoControl) != MH_OK) return 1;
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, InitializeDeviceIoControlHook, nullptr, 0, nullptr);
    }
    return TRUE;
}
