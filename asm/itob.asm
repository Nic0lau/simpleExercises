%ifndef ITOB_H
%define ITOB_H

;int rax itob(int rdi, char *rsi)
;Converts decimal integer in rdi to ascii sequence of binary characters and
;store them in array pointed by rsi. Returns length of string in rax.
itob:
	mov r8, rbp
	mov rbp, rsp
.loop:
	mov rax, rdi
	and rax, 1

	add rax, '0'
	push rax
	
	shr rdi, 1
	test rdi, rdi
	jnz .loop
	
	push 'b'
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
