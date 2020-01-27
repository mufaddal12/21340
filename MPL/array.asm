;printing a character/digit
%macro print 2
	mov rax, 01
	mov rdi, 01
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro

section .data

arr: dq 10h, 15h, 25h, 67h, 30h
cnt db 05h
new db 0xA
cnt1 db 16
colon db ':'

section .bss
	result resb 10

section .text
global _start

_start:
	mov r8, arr
qq:	mov rax,r8
	call htoa
	print result ,16
	print colon , 1
	mov rax,qword[r8]
	call htoa
	print result ,16
	print new,1
add r8,8
dec byte[cnt]
jnz qq

mov rax,60
mov rdi ,00
syscall

;hex to ascii conversion
htoa:		mov rdi,result
		mov byte[cnt1],16
up:
		rol rax, 04
		mov bl,al
		and bl, 0x0F
		cmp bl, 09h
		jbe x
		add bl, 07h
	x:	add bl, 30h
		
		mov byte[rdi], bl
		inc rdi
		dec byte[cnt1]
		jnz up
RET
	
