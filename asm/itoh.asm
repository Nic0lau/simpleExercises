%ifndef ITOH_H
%define ITOH_H

;int rax itoh(int rdi, char *rsi)
;Converts decimal integer in rdi to ascii sequence of hex characters and store
;them in array pointed by rsi. Returns length of string in rax.
itoh:
	mov r8, rbp
	mov rbp, rsp
.loop:
	mov rax, rdi
	and rax, 0b1111
	
	cmp rax, 10
	jl ._not_letter
	
	add rax, 7
._not_letter:
	add rax, '0'
	push rax
	
	shr rdi, 4
	test rdi, rdi
	jnz .loop
	
	push 'x'
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
