#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "Common.h"
#include <ctime>

VOID PrintShellCode(PBYTE pshellCode, SIZE_T size, PBYTE key) {
    int temp = 0;
    std::cout << "BYTE Key = 0x"
        << std::setfill('0') << std::setw(2)
        << std::hex << std::uppercase
        << static_cast<int>(*key) << ";";

    std::cout << "\nunsigned char Shellcode[] = {\n";
    std::cout << "\t";
    for (int i = 0; i < size; i++) {
        if (temp == 16) { // groups of 16
            std::cout << "\n\t";
            temp = 0;
        }
        if (i == size - 1) { //last member
            std::cout << "0x"
                << std::setfill('0') << std::setw(2) << std::hex
                << std::uppercase << static_cast<int>(pshellCode[i]) << " ";
        }
        else {
            std::cout << "0x"
                << std::setfill('0') << std::setw(2) << std::hex
                << std::uppercase  << static_cast<int>(pshellCode[i]) << ", ";
            temp++;
        }
    }
    std::cout << "\n\};";

   

    std::cout << "\n\nBOOL XorDecrypt(IN PBYTE pShellCode, IN SIZE_T NumberOfElements, IN BYTE key, OUT PBYTE& pDShellCode, OUT SIZE_T& pdSizeShellCode) {" << std::endl
        << "    PBYTE buffer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, NumberOfElements);" << std::endl
        << "    if (!buffer) {" << std::endl
        << "        return FALSE;  // Heap allocation failed" << std::endl
        << "    }" << std::endl
        << std::endl
        << "    for (size_t i = 0; i < NumberOfElements; i++) {" << std::endl
        << "        buffer[i] = pShellCode[i] ^ key;" << std::endl
        << "    }" << std::endl
        << std::endl
        << "    pDShellCode = buffer;" << std::endl
        << "    pdSizeShellCode = NumberOfElements;" << std::endl
        << std::endl
        << "    HeapFree(GetProcessHeap(), 0, buffer);" << std::endl
        << std::endl
        << "    return TRUE;" << std::endl
        << "}" << std::endl;
    
}

// Encrypt/Decrypt function
VOID XorEncrypt(IN PBYTE pShellCode, IN SIZE_T NumberOfElements, IN BYTE key) {
    for (size_t i = 0; i < NumberOfElements; i++) {
        pShellCode[i] = pShellCode[i] ^ key;
    }
}

BOOL XorDecrypt(IN PBYTE pShellCode, IN SIZE_T NumberOfElements, IN BYTE key, OUT PBYTE& pDShellCode, OUT SIZE_T& pdSizeShellCode) {

    PBYTE buffer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, NumberOfElements);
    if (!buffer) {
        return FALSE;  // Heap allocation failed
    }

    for (size_t i = 0; i < NumberOfElements; i++) {
        buffer[i] = pShellCode[i] ^ key;
    }


    pDShellCode = buffer;
    pdSizeShellCode = NumberOfElements;


    HeapFree(GetProcessHeap(), 0, buffer);

    return TRUE;
}

// Generate a random Byte key from 0-255
BYTE GenerateKey() {
    BYTE random = rand() % 256;
    return random;
}