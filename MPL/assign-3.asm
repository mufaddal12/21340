%macro print 2
	mov rax, 01
	mov rdi, 01
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro

%macro input 2
	mov rax, 00
	mov rdi, 00
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro

%macro exit 0
	mov rax, 60
	mov rdi, 00
	syscall
%endmacro

section .data
	menu db 0xA,
	db "1. HEX to BCD", 0xA,
	db "2. BCD to HEX", 0xA,
	db "0. Exit", 0xA,
	db " Select an option : ", 0xA
	lenmenu equ $-menu
	option db 2

	digits db 4
	number db 4
	indigs db 1

	index db 0
	
	nl: db 0xA

section .text

global _start

_start:
;--------------------Display Menu and take option-----------------
	print menu, lenmenu
	input option, 2
	mov al, [option]
	cmp al, 31
	jz case1
	cmp al, 32
	jz case1
	cmp al, 30
	jz case3
;-------------------------all option cases-------------------
case1:
	input number, [digits]
	dec al
	mov r8, 0h
	mov [indigs], al
	mov cl, [indigs]
	mov rax, number
	call atoh
	
	

case2:
case3:	exit


atoh:
atohloop:
	mov bl, [rax]
	cmp bl, 39h
	jbe dig
	sub bl, 7h
dig:	sub bl, 30h
	
	mov [rax], bl
	inc rax
	dec cl
	jnz atohloop
ret	




















