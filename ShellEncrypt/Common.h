#pragma once
#include <Windows.h>

VOID PrintShellCode(PBYTE shellCode, SIZE_T size);
VOID XorEncrypt(PBYTE shellCode, SIZE_T size, BYTE key);
BYTE GenerateKey();
BOOL ReadPayload(IN const char* FilePath, OUT PSIZE_T fileSize, OUT PBYTE* pPayload);
BOOL WriteNewPayload(IN const char* FilePath, IN PBYTE pPayload, IN SIZE_T dwfileSize);