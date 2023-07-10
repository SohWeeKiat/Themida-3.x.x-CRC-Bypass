# Themida V3.x.x Cyclic Redundancy Check Bypass
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](../LICENSE.md)

## Introduction
Themida by Oreans is one of the popular software protectors that is known to keep an attacker from reverse engineering a compiled application. One of their feature, particularly CHECK_CODE_INTEGRITY macro, fallshort on WINAPI based bypass. This project is a Prove of Concept(PoC) of an attack vector via WinAPI with no modifications to their CHECK_CODE_INTEGRITY virtual routine. 

## How it works
Once the macro is used, Themida will produce the following procedures:
1. Virtual Machine(VM) Entry (Store existing register values onto the stack, increment lock value in VM context and proceed to jmp to VM handler)
1. VM will proceed to call VirtualAlloc with .text section size, size is retrieved within .themida section
1. I assumed memcpy was used, generating the "repe movsb" instructions, this will copy the .text section to the memory block given by VirtualAlloc
   
    ![](/Images/Screenshot1.jpg)
   
1. Calculate CRC value using the memory block allocated by VirtualAlloc
1. VirtualFree the memory block
1. Original CRC is read from .themida section, compared against calculated CRC and proceeded to assign the variable value if CRC matches 
1. VM Exit (Restore registers from VM Context)

With that, we can see that the weakness is the simple usage of WinAPI VirtualAlloc with .text section size, by monitoring this API with .text section size, we can know when Themida is about to calculate the CRC. 

As shown in the PoC code, after the memory allocation block is given, the original memory is copied onto the memory block and is set to Read-Only, this is purposely done to induce Access Violation when they execute "repe movsb" instructions.

A Vector Exception Handler is added to handle that Access Violation, by modifying the RIP register to skip over the instruction.

## Disclaimer :warning:
**This project is strictly for educational purposes. It is not intended to be a ready-to-be-used library or an attack on the company's products.**
