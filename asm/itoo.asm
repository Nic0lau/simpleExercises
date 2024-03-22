%ifndef ITOO_H
%define ITOO_H

;int rax itoo(int rdi, char *rsi)
;Converts decimal integer in rdi to ascii sequence of octal characters and
;store them in array pointed by rsi. Returns length of string in rax.
itoo:
	mov r8, rbp
	mov rbp, rsp
.loop:
	mov rax, rdi
	and rax, 0b111

	add rax, '0'
	push rax
	
	shr rdi, 3
	test rdi, rdi
	jnz .loop
	
	push 'o'
	push '0'

	xor r10, r10	
.store_loop:
	pop rdi
	cmp qword [rbp], rdi
	je .end
	mov [rsi+r10], rdi
	inc r10
	jmp .store_loop

.end:
	push rdi
	inc r10
	mov rax, r10
	mov rsp, rbp
	mov rbp, r8
	ret
%endif
