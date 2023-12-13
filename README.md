# ShellCode-Encrypt

## Objective:
This C++ program takes in a raw shellcode file (calc.bin) generated from msfvenom and encrypts it using the XOR bitwise operator.

## Purpose
The goal of this project was so I could put into practice the basics learned from Malware Development, using C/C++ and the Windows API.
This code is meant for research/educational purposes only.

## Features
- Supports Raw payloads.
- XOR Encryption with a randomized key.
- Can output to a file if ran with ```.\2ShellEncrypt.exe C:\Users\MyUser\calc.bin > Output.txt```

## Example:

### Generate a Raw Payload with msfvenom:
```bash
msfvenom -p windows/x64/exec CMD="calc.exe" -f raw -o calc.bin
```

### Run the program and pass the payload as an argument
```powershell
.\2ShellEncrypt.exe C:\Users\MyUser\calc.bin
```
It will output an encoded shellcode variable along with the encryption key.

![Tux, the Linux mascot](/img.png)

An optional Decrypt statement is included for debuging/confirmation process. Check the source code for the actual encryption function.