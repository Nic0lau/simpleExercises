%define LOAD_ADDRESS 0x00010000
%define CODE_SIZE END-(LOAD_ADDRESS+0x78)
%define NUM_BUF_SIZE 4096

BITS 64
org LOAD_ADDRESS
ELF_HEADER:
	db 0x7F, "ELF"
	db 0x02
	db 0x01
	db 0x01
	db 0x03
	db 0x00
	times 7 db 0x00
	dw 0x0002
	dw 0x003E
	dd 0x00000001
	dq START
	dq 0x0000000000000040
	dq 0x0000000000000000
	dd 0x00000000
	dw 0x0040
	dw 0x0038
	dw 0x0001
	dw 0x0000
	dw 0x0000
	dw 0x0000
PROGRAM_HEADER:
	dd 0x00000001
	dd 0x00000007
	dq 0x0000000000000078
	dq LOAD_ADDRESS+0x78
	dq 0x0000000000000000
	dq CODE_SIZE
	dq CODE_SIZE+NUM_BUF_SIZE
	dq 0x0000000000000000

%include "dumpReg.asm"
%include "dumpStack.asm"
%include "dumpMem.asm"

START:

	push qword 69
	mov rdi, 1
	mov rsi, NUM_BUF
	mov rdx, 4
	call dump_stack

	mov rdi, 1
	mov rsi, NUM_BUF
	mov rdx, SOME_SHIT
	mov rcx, 56
	call dump_mem

	;Reading and writing at the same buffer at the same time, but in
	;different positions. So the output is the hex of the ascii value
	;for the letters in the output message.
	mov rdi, 1
	mov rsi, NUM_BUF
	mov rdx, NUM_BUF
	mov rcx, 512
	call dump_mem

	push qword NUM_BUF
	push qword 1
	call dump_reg

	mov rax, 60
	mov rdi, 0
	syscall

SOME_SHIT:
	db 1, 2, 3, 4, 5, 6, 7, 8
	db 9, 10, 11, 12, 13, 14, 15, 16
	db 17, 18, 19, 20, 21, 22, 23, 24
	times 8 db "ELF"

	dq CODE_SIZE+NUM_BUF_SIZE
END:
NUM_BUF:
