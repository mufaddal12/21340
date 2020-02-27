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

%macro openFile 1
	mov rax, 2
	mov rdi, %1
	mov rsi, 2
	mov rdx, 0777
	syscall
%endmacro

%macro closeFile 1
	mov rax, 3
	mov rdi, %1
	syscall
%endmacro

%macro readFile 3
	mov rax,00
	mov rdi,%1
	mov rsi,%2
	mov rdx,%3
	syscall
%endmacro

%macro writeFile 3
	mov rax,01
	mov rdi,%1
	mov rsi,%2
	mov rdx,%3
	syscall
%endmacro

%macro exit 0
	mov rax, 60
	mov rdi, 00
	syscall
%endmacro
	
section .data
	fname : db "a7d.txt", 0

	errormsg : db "File Not Found", 0xA
	errorlen : equ $-errormsg

	opensuccess : db "File Opened Successfully", 0xA
	openlen : equ $-opensuccess

	orgArray : db "Original Array : "
	orglen : equ $-orgArray

	sortArray : db "Sorted Array : "
	sortlen : equ $-sortArray
	nl: db 0xA
section .bss
	fd: resb 8
	buffer: resb 200
	n: resq 1
section .txt

global _start

_start:

	openFile fname
	mov [fd], rax
	bt rax, 63
	jc fileerror
	print opensuccess, openlen
	readFile [fd], buffer, 200
	mov [n], rax
	
	print orgArray, orglen
	print buffer, n
	print nl, 1

	call bubbleSort

	print sortArray, sortlen
	print buffer, n
	print nl, 1

writeFile [fd], buffer, [n]
closeFile [fd]
exit
	
fileerror:
	print errormsg, errorlen
	
exit	
	
bubbleSort:
	mov rcx, 0
	
	mov rdx, [n]
	mov rsi, buffer
outer:	
	mov r8, 0
	
	inner:	
		mov r9, r8
		inc r9

		mov al, byte[rsi+r8]
		mov bl, byte[rsi+r9]
		cmp al, bl
		jb noSwap
		mov ah, al
		mov al, bl
		mov bl, ah
	noSwap:
		mov byte[rsi+r8], al
		mov byte[rsi+r9], bl
		inc r8
		inc r9
		cmp r8, rdx
		jl inner
	inc rcx
	cmp rcx, rdx
	jl outer
ret

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
