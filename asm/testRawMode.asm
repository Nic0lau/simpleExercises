%define LOAD_ADDRESS 0x00010000
%define CODE_SIZE END-(LOAD_ADDRESS+0x78)
%define WRITE_BUF_SIZE 20

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
	dq CODE_SIZE+WRITE_BUF_SIZE
	dq 0x0000000000000000
%include "syscalls.asm"
%include "toggleRawMode.asm"
%include "itoa.asm"
START:
	mov rdi, 0
	call toggle_raw_mode
.read_loop:
	mov dword [READ_BUF], 0
	mov rcx, WRITE_BUF_SIZE 
	mov al, 0
	mov rdi, WRITE_BUF
	rep stosb 

	mov rax, __NR_READ
	mov rdi, 0
	mov rsi, READ_BUF
	mov rdx, 4 
	syscall
	
	mov r11, rax
	xor r12, r12 ;for (r12 = 0;r12 < READ_BUF.length;r12++)
	xor r13, r13

.write_loop:
	movzx rdi, byte [READ_BUF+r12]
	mov rsi, WRITE_BUF
	add rsi, r13
	push r11
	call itoa
	pop r11

	add r13, rax
	mov byte [WRITE_BUF+r13], 0x20 
	inc r13

	inc r12
	cmp r12, r11
	jne .write_loop

	mov byte [WRITE_BUF+r13-1], 0x0A

	mov rax, __NR_WRITE
	mov rdi, 1
	mov rsi, WRITE_BUF
	mov rdx, r13
	syscall

	cmp byte [READ_BUF], 'q'
	je .leave
	jmp .read_loop
.leave:
	mov rdi, 1
	call toggle_raw_mode

	mov rax, __NR_EXIT
	mov rdi, 69
	syscall
READ_BUF:
	times 4 db 0
END:
WRITE_BUF:
