%ifndef ATOI_H
%define ATOI_H
;int atoi(char *rdi, int rsi)
;Converts rsi characters of a string pointed to by rdi into an int. Returns
;the integer number.
atoi:
	add rdi, rsi
	dec rdi
	mov r11, 1
.loop:
	cmp byte [rdi], '-'
	je .negative
	movzx rax, byte [rdi]
	sub rax, '0'

	mul r11
	add r12, rax

	imul r11, 10

	dec rdi
	dec rsi
	jnz .loop
	jmp .end
.negative:
	neg r12
.end:
	mov rax, r12
	ret
%endif
