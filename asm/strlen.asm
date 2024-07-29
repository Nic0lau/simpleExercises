%ifndef STRLEN_H
%define STRLEN_H
;int strlen(char *rdi)
;Returns length of a C-string in rax.
strlen:
	xor rcx, rcx
	dec rcx
	repnz scasb

	neg rcx
	mov rax, rcx

	ret
%endif
