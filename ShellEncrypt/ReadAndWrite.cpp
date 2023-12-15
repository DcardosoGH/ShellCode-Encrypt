#include <Windows.h>
#include <iostream>
#include "Common.h"

BOOL ReadPayload(IN const char* FilePath, OUT PSIZE_T pfileSize, OUT PBYTE* ppPayload) {
    HANDLE hFile = INVALID_HANDLE_VALUE;
    DWORD fileSize = NULL;
    DWORD lpNumberOfBytesRead = NULL;

    // Create a handle on the file to be read
    hFile = CreateFileA(FilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "CreateFileA error: " << GetLastError() << std::endl;
        return FALSE;
    }

    // Calculate its size
    *pfileSize = GetFileSize(hFile, NULL);
    if (*pfileSize == INVALID_FILE_SIZE) {
        std::cout << "GetFileSize error " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return FALSE;
    }

    // allocate a new buffer that will receive it
    unsigned char* Payload = (unsigned char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, *pfileSize);
    if (Payload == NULL) {
        std::cout << "HeapAlloc error." << GetLastError() << std::endl;
        CloseHandle(hFile);
        return FALSE;
    }

    // Read the file to the buffer
    if (!ReadFile(hFile, Payload, *pfileSize, &lpNumberOfBytesRead, NULL)) {
        CloseHandle(hFile);
        std::cout << "Error Reading File: " << GetLastError() << std::endl;
        return FALSE;
    }

    // Since we passed a pointer to a pointer, this effectively makes the Payload on main() to receive the newly allocated Payload
    *ppPayload = Payload;

    return TRUE;
}


BOOL WriteNewPayload(IN const char* FilePath, IN PBYTE pPayload, IN SIZE_T dwfileSize) {
    DWORD	lpNumberOfBytesWritten = NULL;
    HANDLE hFile = CreateFileA(FilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "CreateFileA error: " << GetLastError() << std::endl;
        return -1;
    }

    // Condition to check if file is successfully written, the OR statement will run after the WriteFile, so it acts as a double check
    if (!WriteFile(hFile, pPayload, dwfileSize, &lpNumberOfBytesWritten, NULL) || dwfileSize != lpNumberOfBytesWritten) {
        std::cout << "WriteFile error: " << GetLastError() << std::endl;
        return -1;
    }
}