%ifndef ITOA_H
%define ITOA_H

;int rax itoa(int rdi, char *rsi)
;Converts decimal integer in rdi to ascii sequence of characters and store
;them in array pointed by rsi. Returns length of string in rax.
itoa:
	mov r8, rbp
	mov rbp, rsp

	mov r11, rdi
	mov rax, rdi
	test rax, rax
	jns .positive
	neg rax
.positive:
	mov rdi, 10
.loop:
	xor rdx, rdx
	div rdi
	
	add rdx, '0'
	push rdx
	
	test rax, rax
	jnz .loop
	
	test r11, r11
	jns .store_in_array
	push 0x2D
.store_in_array:
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
