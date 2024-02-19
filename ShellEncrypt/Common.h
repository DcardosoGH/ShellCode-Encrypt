#pragma once
#include <Windows.h>

VOID PrintShellCode(PBYTE shellCode, SIZE_T size, PBYTE key);
VOID XorEncrypt(IN PBYTE pShellCode, IN SIZE_T NumberOfElements, IN BYTE key);
BOOL XorDecrypt(IN PBYTE pShellCode, IN SIZE_T NumberOfElements, IN BYTE key, OUT PBYTE& pDShellCode, OUT SIZE_T& pdSizeShellCode);
BYTE GenerateKey();
BOOL ReadPayload(IN const char* FilePath, OUT PSIZE_T fileSize, OUT PBYTE* pPayload);
BOOL WriteNewPayload(IN const char* FilePath, IN PBYTE pPayload, IN SIZE_T dwfileSize);