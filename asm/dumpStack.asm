%ifndef DUMP_STACK_H
%define DUMP_STACK_H

%include "itoh.asm"
%include "itoa.asm"

;void dump_stack(int rdi, char *rsi, int rdx)
;Dumps the value of rdx quadwords above the current rsp to the file 
;descriptor specified by rdi. Buffer is indicated by rsi and is recommended 
;to be at least rdx*28, since it will contain the entire output string.
dump_stack:

	push rbp
	shl rdx, 3 ;converting from quadwords to bytes	
	xor r9, r9 ;used as length of final string
	mov rbp, rsp ;rbp is the offset of current value to print
	add rbp, rdx
	add rbp, 8
	mov r10, rdi
.loop:
	mov rcx, 4
	mov rdi, rsi
	mov rsi, .format
	rep movsb
	mov rsi, rdi
	add r9, 4

	mov rdi, rdx
	push rdx
	push r10
	call itoa
	pop r10
	pop rdx

	mov byte [rsi+rax], ':'
	inc rax
	
	add r9, rax
	add rsi, rax
	
	mov rdi, [rbp]
	push r10
	call itoh
	pop r10

	mov byte [rsi+rax], 10
	inc rax
	
	add r9, rax
	add rsi, rax

	sub rbp, 8
	sub rdx, 8
	jns .loop

	mov rax, 1
	mov rdi, r10
	sub rsi, r9
	mov rdx, r9
	syscall
	
	pop rbp
	ret	
	
.format:
	db "rsp+"
%endif
