%define LOAD_ADDRESS 0x00010000
%define CODE_SIZE END-(LOAD_ADDRESS+0x78)
%define READ_BUF_SIZE 4096

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
	dq CODE_SIZE+READ_BUF_SIZE
	dq 0x0000000000000000
START:
	cmp byte [RSP], 1
	jle ERR_NOT_ENOUGH_ARGS
	
	xor rbx, rbx
	inc rbx
_file_open_loop:	
	inc rbx
	
	cmp byte [RSP+RBX*8], 0
	je OK_EXIT
	
	mov rdi, [RSP+RBX*8]
	xor rsi, rsi
	xor rax, rax
	xor rdx, rdx
	
	mov rax, 2
	syscall
	
	cmp RAX, 0
	jl ERR_OPENING_FILE
	
	mov R12, RAX
__file_read_loop:
	mov RAX, 0
	mov RDI, R12
	mov RSI, READ_BUF
	mov RDX, READ_BUF_SIZE
	syscall

	cmp RAX, 0
	je __file_close

	mov RDX, RAX
	mov RAX, 1
	mov RDI, 1
	mov RSI, READ_BUF
	syscall
	jmp __file_read_loop

__file_close:
	mov RAX, 3
	mov RDI, R12
	syscall
	
	jmp _file_open_loop
OK_EXIT:
	mov RAX, 60
	mov RDI, 0
	syscall
ERR_NOT_ENOUGH_ARGS:
	mov RAX, 1
	mov RDI, 2
	mov RSI, ERR_NOT_ENOUGH_ARGS_MSG
	mov RDX, ADDRESS_AFTER_MSGA-ERR_NOT_ENOUGH_ARGS_MSG
	syscall
	
	mov RAX, 60
	mov RDI, 1
	syscall
ERR_NOT_ENOUGH_ARGS_MSG:
	db "Usage: [program] [files]", 10
ADDRESS_AFTER_MSGA:
ERR_OPENING_FILE:
	mov RAX, 1
	mov RDI, 1
	mov RSI, ERR_OPENING_FILE_MSG
	mov RDX, ADDRESS_AFTER_MSGB-ERR_OPENING_FILE_MSG
	syscall
	
	mov RAX, 60
	mov RDI, 1
	syscall
ERR_OPENING_FILE_MSG:
	db "Error opening file", 10
ADDRESS_AFTER_MSGB:
END:
READ_BUF:
