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

section .bss

section .text
	global asciitohex
	global hextoascii
	global countspaces
	global countnewlines

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

;-------------------------Count spaces--------------------------

countspaces:

ret

;-----------------------Count new Lines-------------------------

countnewlines:

ret

















