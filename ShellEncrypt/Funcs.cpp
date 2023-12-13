#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "Common.h"
#include <ctime>

VOID PrintShellCode(PBYTE pshellCode, SIZE_T size) {
    int temp = 0;
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
}


VOID XorEncrypt(PBYTE pshellCode, SIZE_T size, BYTE key) {
    std::cout << "\nThe encryption key is: 0x"
        << std::setfill('0') << std::setw(2)
        << std::hex << std::uppercase
        << static_cast<int>(key);
    for (size_t i = 0; i < size; i++) {
        pshellCode[i] = pshellCode[i] ^ key;
    }
}

BYTE GenerateKey() {
    BYTE random = rand() % 256;
    return random;
}