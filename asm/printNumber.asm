%define LOAD_ADDRESS 0x00010000
%define CODE_SIZE END-(LOAD_ADDRESS+0x78)
%define NUM_BUF_SIZE 32

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

%include "itoa.asm"
%include "itoh.asm"
%include "itoo.asm"
%include "itob.asm"

START:
	mov rdi, -42069
	mov rsi, NUM_BUF
	call itoa

	mov byte [NUM_BUF+rax], 10
	inc rax
	
	mov rdx, rax
	mov rax, 1
	mov rdi, 1
	mov rsi, NUM_BUF
	syscall

	mov rdi, -42069
	mov rsi, NUM_BUF
	call itoh
	
	mov byte [NUM_BUF+rax], 10
	inc rax
	
	mov rdx, rax
	mov rax, 1
	mov rdi, 1
	mov rsi, NUM_BUF
	syscall

	mov rdi, -42069
	mov rsi, NUM_BUF
	call itoo
	
	mov byte [NUM_BUF+rax], 10
	inc rax
	
	mov rdx, rax
	mov rax, 1
	mov rdi, 1
	mov rsi, NUM_BUF
	syscall

	mov rdi, -42069
	mov rsi, NUM_BUF
	call itob
	
	mov byte[NUM_BUF+rax], 10
	inc rax
	
	mov rdx, rax
	mov rax, 1
	mov rdi, 1
	mov rsi, NUM_BUF
	syscall

	mov rax, 60
	mov rdi, 0
	syscall
END:
NUM_BUF:
