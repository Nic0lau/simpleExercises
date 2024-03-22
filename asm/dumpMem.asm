%ifndef DUMP_MEM_H
%define DUMP_MEM_H

%include "itoh.asm"

;void dump_mem(int rdi, char *rsi, byte *rdx, int rcx)
;Prints rcx bytes starting by the byte pointed to by rdx to the file descriptor
;specified by rdi, using rsi as buffer.

dump_mem:
	push r12
	xor r9, r9 ;used as counter for length of string
	mov r11, rdi
.line_loop:
	mov byte [rsi], 10
	inc rsi
	inc r9

	mov rdi, rdx
	call itoh
	
	mov byte [rsi+rax], ':'
	inc rax

	add r9, rax
	add rsi, rax
	
	mov r12, 16
.byte_loop:
	mov byte [rsi], ' '
	inc rsi
	inc r9
	
	movzx rdi, byte [rdx]
	call itoh
	
	add r9, rax
	add rsi, rax
	inc rdx
	
	dec rcx
	jz .end

	dec r12
	jnz .byte_loop
	jmp .line_loop

.end:
	mov rax, 1
	mov rdi, r11
	sub rsi, r9
	mov rdx, r9
	syscall

	pop r12
	ret
%endif
