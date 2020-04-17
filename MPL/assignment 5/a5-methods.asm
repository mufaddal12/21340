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
	extern chars, lines, spaces

section .bss
	extern buffer, bufferlen, character
	result resb 2
section .text
	global hextoascii, countspaces, countlines, countchar

;-------------------------hex to ascii method-------------------

hextoascii:
	mov rsi, result
	mov cl, 02
	loop3:
		rol al, 04h
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
	print result, 2
ret

;-------------------------Count spaces--------------------------

countspaces:
	mov rcx, qword[bufferlen]
	mov byte[spaces], 0
	mov rsi, buffer

spaceup:
	cmp byte[rsi], ' '
	jnz noincremspaces
	inc byte[spaces]
noincremspaces:
	inc rsi
	dec rcx
	jnz spaceup
	mov al, [spaces]
	call hextoascii
ret

;-----------------------Count new Lines-------------------------

countlines:
	mov rcx, qword[bufferlen]
	mov byte[lines], 0
	mov rsi, buffer

lineup:
	cmp byte[rsi], 0xA
	jnz noincremlines
	inc byte[lines]
noincremlines:
	inc rsi
	dec rcx
	jnz lineup
	mov al, [lines]
	call hextoascii
ret

;---------------------Counting character-------------------------

countchar:
	mov rcx, qword[bufferlen]
	mov byte[chars], 0
	mov rsi, buffer
	mov al, byte[character]
charup:
	cmp byte[rsi], al
	jnz noincremchars
	inc byte[chars]
noincremchars:
	inc rsi
	dec rcx
	jnz charup
	mov al, [chars]
	call hextoascii
ret












