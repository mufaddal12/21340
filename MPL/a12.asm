%macro write 3
	mov rax, 01
	mov rdi, %1
	mov rsi, %2
	mov rdx, %3
	syscall
%endmacro

%macro read 3
	mov rax, 00
	mov rdi, %1
	mov rsi, %2
	mov rdx, %3
	syscall
%endmacro

%macro openFile 1
	mov rax, 2
	mov rdi, %1
	mov rsi, 0102o
	mov rdx, 0666o
	syscall
%endmacro

%macro closeFile 1
	mov rax, 3
	mov rdi, %1
	syscall
%endmacro

%macro exit 0
	mov rax, 60
	mov rdi, 00
	syscall
%endmacro

section .data

	array: dd 10.00, 20.00, 50.00, 60.00, 50.00

	meanmsg: db "Mean : "
	meanlen: equ $-meanmsg

	varmsg: db "Variance : "
	varlen: equ $-varmsg

	stdmsg: db "Standard deviation : "
	stdlen: equ $-stdmsg

	dec: dd 100
	n: dd 5
	dot: db "."
	nl : db 0xA
section .bss
	mean: resd 1
	var: resd 1
	buffer: rest 1
	result: resb 1
section .txt
global _start
_start:
	finit
	fldz
	mov rsi, array
	mov ecx, dword[n]

sumloop:
	fadd dword[rsi]
	add rsi, 4
	dec ecx
	jnz sumloop
	
	fidiv dword[n]
	fst dword[mean]
	
	write 01, meanmsg, meanlen
	call print
	write 01, nl, 1
	
	mov rsi, array
	mov ecx, dword[n]

	fldz
varloop:
	fldz
	fld dword[rsi]
	fsub dword[mean]
	fmul st0
	inc rsi
	dec ecx
	jnz varloop
	
	fidiv dword[n]
	fst dword[var]
	write 01, varmsg, varlen
	call print
	write 01, nl, 1
	exit
	

print:
	fimul dword[dec]
	fbstp tword[buffer]
	mov rsi, buffer
	add rsi, 09
	mov cx, 09
whole:
	mov al, byte[rsi]
	push cx
	push rsi
	call hextoascii
	pop rsi
	pop cx
	dec rsi
	dec cx
	jnz whole
	
	write 01, dot, 1

	mov rsi, buffer
	mov al, byte[buffer]
	call hextoascii
ret	
	
hextoascii:
	mov rsi, result
	mov cl, 2
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
	write 01, result, 2
ret	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
