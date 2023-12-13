#include <Windows.h>
#include <iostream>
#include "Common.h"

BOOL ReadPayload(IN const char* FilePath, OUT PSIZE_T pfileSize, OUT PBYTE* ppPayload) {
    HANDLE hFile = INVALID_HANDLE_VALUE;
    DWORD fileSize = NULL;
    DWORD lpNumberOfBytesRead = NULL;

    hFile = CreateFileA(FilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "CreateFileA error: " << GetLastError() << std::endl;
        return FALSE;
    }

    *pfileSize = GetFileSize(hFile, NULL);
    if (*pfileSize == INVALID_FILE_SIZE) {
        std::cout << "GetFileSize error " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return FALSE;
    }


    unsigned char* Payload = (unsigned char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, *pfileSize + 1);
    if (Payload == NULL) {
        std::cout << "HeapAlloc error." << GetLastError() << std::endl;
        CloseHandle(hFile);
        return FALSE;
    }

    if (!ReadFile(hFile, Payload, *pfileSize, &lpNumberOfBytesRead, NULL)) {
        CloseHandle(hFile);
        std::cout << "Error Reading File: " << GetLastError() << std::endl;
        return FALSE;
    }

    *ppPayload = Payload;

    return TRUE;
}