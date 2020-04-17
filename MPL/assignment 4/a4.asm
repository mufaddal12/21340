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
	msg1 : db "Number 1 : "
	len1 : equ $-msg1
	msg2 : db "Number 2 : "
	len2 : equ $-msg2
	nl : db 0xA
	menu : db 0xA,
	db "1. Successive addition method",0xA,
	db "2. Add and shift method", 0xA,
	db "0. Exit", 0xA,
	db "  Option : "
	menulen: equ $-menu
	
section .bss
	num1 resb 1
	num2 resb 1
	inputnum resb 2
	result resb 4
	opt resb 2
section .text
global _start

_start:
;------------------------Display Menu and take option--------------------
	print menu, menulen
	input opt, 2
	print nl, 1
	mov al, byte[opt]
	cmp al, 31h
	jz case1
	cmp al, 32h
	jz case2
	cmp al, 30h
	jz case3
;-------------------------------All option cases-------------------------

case1:	
	print msg1, len1
	input inputnum, 3
	call asciitohex
	mov byte[num1], al

	print msg2, len2
	input inputnum, 3
	call asciitohex
	mov byte[num2], al

;multiplication
	call succ_add
	call hextoascii
	print result, 4
	print nl, 1
	exit

case2:
	print msg1, len1
	input inputnum, 3
	call asciitohex
	mov byte[num1], al

	print msg2, len2
	input inputnum, 3
	call asciitohex
	mov byte[num2], al

;multiplication
	call add_shift
	call hextoascii
	print result, 4
	print nl, 1
	exit
case3: 
	exit
;-------------------------ascii to hex method--------------------

asciitohex:
	mov cl, 2
	mov rsi, inputnum
	xor ax, ax
	xor bx, bx
atohloop:
	rol ax, 4
	mov bl, byte[rsi]
	cmp bl, 39h
	jbe sub30
	sub bl, 07h
sub30:
	sub bl, 30h
	add ax, bx	
	inc rsi
	dec cl
	jnz atohloop	
ret	

;-------------------------hex to ascii method-------------------

hextoascii:
	mov rsi, result
	mov cl, 04
	loop3:
		rol ax, 04h
		mov bl, al
		and bl, 0x0F
		cmp bl, 09h
		jbe x
		add bl, 07h
	x:	add bl, 30h	
		mov byte[rsi], bl
		inc rsi

		dec cl
		jnz loop3
ret

;---------------------successive addition--------------------

succ_add:
	xor cx, cx
	xor dx, dx
	xor ax, ax

	mov dl, byte[num1]
	mov cl, byte[num2]
	cmp cl, 00h
	jz zeroans
	
up:	add ax, dx
	dec cl
	jnz up
	ret
zeroans:
	mov ax, 0h
	ret

;---------------------add-shift method-----------------
add_shift:
	xor ax, ax
	xor dx, dx
	xor bx, bx

	mov bl, byte[num1]
	mov dl, byte[num2]
	mov cl, 08
addshiftloop:
	shl ax, 01
	shl bl, 01
	jnc noadd
	add ax, dx
noadd:
	dec cl
	jnz addshiftloop
ret












