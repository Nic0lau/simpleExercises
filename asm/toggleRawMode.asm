%ifndef TOGGLE_RAW_MODE_H
%define TOGGLE_RAW_MODE_H
%include "syscalls.asm"

;These are from /usr/include/asm-generic/ioctls.h
%define TCGETS 0x5401
%define TCSETS 0x5402
;These are from /usr/include/bits/termios-c_[io(cf)l]flag.h
%define IGNBRK  0x1 
%define BRKINT  0x2 
%define PARMRK  0x8
%define ISTRIP  0x20
%define INLCR   0x40
%define IGNCR   0x80
%define ICRNL   0x100
%define IXON    0x400

%define OPOST 0x1

%define ISIG 0x1 
%define ICANON 0x2
%define ECHO 0x8
%define ECHONL 0x40
%define IEXTEN 0x10000

%define CSIZE 0x30
%define PARENB 0x100
%define CS8 0x30

;int toggle_raw_mode(int rdi)
;Turns raw mode on if rdi is 0, turns off if rdi is nonzero.
;Returns 0 in rax on success.
toggle_raw_mode:
	test rdi, rdi
	jnz .disable
.enable:
	mov rax, __NR_IOCTL
	mov rdi, 0
	mov rsi, TCGETS
	mov rdx, .old_termios
	syscall

	mov rax, __NR_IOCTL
	mov rdi, 0
	mov rsi, TCGETS
	mov rdx, .new_termios
	syscall

	and dword [.new_termios], ~(IGNBRK + BRKINT + PARMRK + ISTRIP + INLCR + IGNCR + ICRNL + IXON)
	and dword [.new_termios + 4], ~OPOST
	and dword [.new_termios + 8], ~(CSIZE + PARENB)
	or dword [.new_termios + 8], CS8
	and dword [.new_termios + 12], ~(ECHO + ECHONL + ICANON + ISIG + IEXTEN)

	mov rax, __NR_IOCTL
	mov rdi, 0
	mov rsi, TCSETS
	mov rdx, .new_termios
	syscall

	jmp .done
.disable:
	mov rax, __NR_IOCTL
	mov rdi, 0
	mov rsi, TCSETS
	mov rdx, .old_termios
	syscall
.done:
	ret

.old_termios:
	times 64 db 0
.new_termios:
	times 64 db 0
%endif
