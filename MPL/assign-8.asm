%macro write 2
	mov rax, 01
	mov rdi, 01
	mov rsi, %1
	mov rdx, %2
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
	mov rsi, 2
	mov rdx, 0777
	syscall
%endmacro

%macro exit 0
	mov rax, 60
	mov rdi, 00
	syscall
%endmacro

section .data
	msg: db "hello world", 0xA
	msglen: equ $-msg

	opensuccess : db "File Opened Successfully", 0xA
	openlen : equ $-opensuccess

	errormsg : db "File Not Found", 0xA
	errorlen : equ $-errormsg

	nl : db 0xA
section .bss
	srcfname: resb 8
	buffer: resb 200
	bufferlen: resq 1
	fd: resb 8
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

typecase:
	pop rax
	mov rbx, [rax]
	mov [srcfname], rbx
	openFile srcfname
	mov [fd], rax
	bt rax, 63
	jc fileerror
	write opensuccess, openlen
	read [fd], buffer, 200
	mov [bufferlen], rax
	write buffer, bufferlen
	write nl, 1
	exit
copycase:
	exit
deletecase:
	exit	
	
fileerror:
	write errormsg, errorlen
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
