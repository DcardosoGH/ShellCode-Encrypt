#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "Common.h"
#include <ctime>


int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage " << argv[0] << " <Shell code file path>" << std::endl;
        return 1;
    }
    const char* filePath = argv[1];

    SIZE_T dwfileSize = NULL;
    PBYTE pPayload = NULL;

    if (!ReadPayload(filePath, &dwfileSize, &pPayload)) {
        return -1;
    }
    
    srand(static_cast<unsigned int>(time(0)));
    BYTE key = GenerateKey();
    XorEncrypt(pPayload, dwfileSize, key);
    PrintShellCode(pPayload, dwfileSize);


   // Optional print of the decrypted payload to confirm it is correct
   // std::cout << "\nPress <Enter> to Decrypt the ShellCode\n";
   // getchar();
   // XorEncrypt(pPayload, dwfileSize, key);
   // PrintShellCode(pPayload, dwfileSize);

    HeapFree(GetProcessHeap(), 0, pPayload);
}