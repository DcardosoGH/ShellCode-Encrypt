# ShellCode-Encrypt

## Objective:
This C++ program takes in a raw shellcode file (calc.bin) generated from msfvenom and encrypts it using the XOR bitwise operator.

## Purpose
The goal of this project was so I could put into practice the basics learned from Malware Development, using C/C++ and the Windows API.
This code is meant for research/educational purposes only.

## Features
- Supports Raw payloads.
- XOR Encryption with a randomized key.

## Output Options
- Write a new raw.bin file with: ```.\2ShellEncrypt.exe .\calc.bin .\newPayload.bin```
	- Make sure to still watch the print statement for the encryption key.
- If this is not specified, the program will output the encrypted shellcode to the console.

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

![Print statement](/img3.png)

To generate a new file simply pass in its name

![Create a new file](/img4.png)

An optional Decrypt statement is included in the Source Code for debuging/confirmation process. 

Check the source code for the actual encryption function.