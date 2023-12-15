#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "Common.h"
#include <ctime>


int main(int argc, char* argv[])
{
    // check for the correct number of arguments
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage " << argv[0] << " <ShellCode file> (Optional)<newPayloadFileName>" << std::endl;
        return 1;
    }
    const char* filePath = argv[1];

    SIZE_T dwfileSize = NULL;
    PBYTE pPayload = NULL;

    // Read the Shellcode file passed in as an argument
    if (!ReadPayload(filePath, &dwfileSize, &pPayload)) {
        return -1;
    }
    
    //feeding a srand for a random number generation
    srand(static_cast<unsigned int>(time(0)));
    BYTE key = GenerateKey();

    //encrypt and print the new shellcode.
    XorEncrypt(pPayload, dwfileSize, key);
    PrintShellCode(pPayload, dwfileSize);


    // Optional print of the decrypted payload to confirm it is correct
    // std::cout << "\nPress <Enter> to Decrypt the ShellCode\n";
    // getchar();
    // XorEncrypt(pPayload, dwfileSize, key);
    // PrintShellCode(pPayload, dwfileSize);

    //If the 3rd argument is passed, write a new file to disk with the shellcode
    if (argc == 3) {
        const char* fileNameToWrite = argv[2];
        WriteNewPayload(fileNameToWrite, pPayload, dwfileSize);
    }


    // Free the allocated memory
    HeapFree(GetProcessHeap(), 0, pPayload);
    return 0;
}