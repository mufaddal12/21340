%macro print 2
	mov rax, 01
	mov rdi, 01
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro

%macro exit 0
	mov rax, 60
	mov rdi, 00
	syscall
%endmacro

section .bss

	input: resb 3
	num: resw 1
	result: resb 8
	
section .txt

global _start

_start:
	pop rax
	pop rax
	pop rax
	mov rax, [rax]
	mov [input], rax
	
	call asciitohex
	
	mov eax, 01
	mov bx, [num]

	call factorial
	
	mov bx, ax
	mov ax, dx
	rol eax, 16
	mov ax, bx	
	call hextoascii

	print result, 8
	exit
	
asciitohex:
	mov cl, 2
	mov rsi, input
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

	mov word[num], ax
ret		
	
hextoascii:
	mov rsi, result
	mov cl, 8
	loop3:
		rol eax, 04h
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
	
factorial:
	cmp bx, 1
	jbe return1
	
	push bx
	
	dec bx
	call factorial
	pop bx	
return1: 
	mul bx
	ret	
	
	
	
	
	
