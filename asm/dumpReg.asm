%ifndef DUMP_REG_H
%define DUMP_REG_H
;void dump_reg(int [rsp+8], char *[rsp+16])
;Dumps the value of all 64-bit general purpose registers (including rflags) to
;file descriptor [rsp+8] and uses [rsp+16] as a buffer for storing the final
;string. In this specific function, all the registers are callee-saved. For
;safety, it is recommended to use a buffer with a minimum size of 400 bytes.
%include "itoh.asm"

dump_reg:
	
	mov [.orig_rsp], rsp

	pushfq
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rdi
	push rsi
	push rbp
	mov r8, [.orig_rsp]
	push r8
	push rbx
	push rdx
	push rcx
	push rax

	mov r12, [.orig_rsp]
	add r12, 8
	mov r12, [r12] ; fd in r12
	mov r13, .str
	mov r14, 17
	mov r15, rsp
	xor r9, r9 ;length of final string
	mov rsi, [.orig_rsp]
	add rsi, 16
	mov rsi, [rsi] ;buffer
.loop:
	mov rcx, 5
	mov rdi, rsi
	mov rsi, r13
	rep movsb
	mov rsi, rdi
	add r9, 5
	add r13, 5

	mov rdi, [r15]
	call itoh
	
	add r9, rax
	add rsi, rax

	add r15, 8
	dec r14
	test r14, r14
	jnz .loop
	
	mov byte [rsi], 10 ;final \n
	inc rsi
	inc r9
	
	mov rax, 1
	mov rdi, r12
	sub rsi, r9
	mov rdx, r9
	syscall

	pop rax
	pop rcx
	pop rdx
	pop rbx
	add rsp, 8
	pop rbp
	pop rsi
	pop rdi
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15
	
	;getting rid of flags, since these can't be restored
	add rsp, 8
	
	ret

.str:
	db `\nrax:\nrcx:\nrdx:\nrbx:\nrsp:\nrbp:\nrsi:\nrdi:`
	db `\nr8 :\nr9 :\nr10:\nr11:\nr12:\nr13:\nr14:\nr15:`
	db `\nflg:`
.orig_rsp:
	dq 0
%endif
