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

	opensuccess : db "File Opened Successfully", 0xA
	openlen : equ $-opensuccess

	errormsg : db "File Not Found", 0xA
	errorlen : equ $-errormsg

	nl : db 0xA
section .bss
	srcf: resb 12
	destf: resb 12
	buffer: resb 200
	bufferlen: resq 1
	fd1: resq 1
	fd2: resq 1
	var: resq 1
section .txt
global _start

_start:
	pop rax
	pop rax
	pop rax
	
	cmp byte[rax], 'T'
	je typecase

	cmp byte[rax], 'C'
	je copycase

	cmp byte[rax], 'D'
	je deletecase

	exit

typecase:
	pop rax
	mov rbx, [rax]
	mov [srcf], rbx
	openFile srcf

	mov [fd1], rax
	bt rax, 63
	jc fileerror

	write 01, opensuccess, openlen
	read [fd1], buffer, 200
	mov qword[bufferlen], rax
	write 01, buffer, [bufferlen]
	;write nl, 1
	exit

copycase:
	pop rax
	mov rbx, [rax]
	mov [srcf], rbx

	openFile srcf
	mov [fd1], rax
	
	bt rax, 63
	jc fileerror

	pop rax
	mov rbx, [rax]
	mov [destf], rbx

	openFile destf
	mov [fd2], rax

	read [fd1], buffer, 200
	mov [bufferlen], rax

	write [fd2], buffer, [bufferlen]
	
	closeFile [fd1]
	closeFile [fd2]

	exit

deletecase:
	pop rbx
	mov rax, 87
	mov rdi, rbx
	syscall
	exit	
	
fileerror:
	write 01,errormsg, errorlen
	exit
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
