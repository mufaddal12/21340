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

%macro readFile 3
	mov rax,00
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
	msg : db "Character : "
	msglen : equ $-msg
	nl : db 0xA
	menu : db 0xA,
	db "1. No. of blank spaces",0xA,
	db "2. No. of lines", 0xA,
	db "3. No. of a character", 0xA,
	db "0. Exit", 0xA,
	db "  Option : "
	menulen: equ $-menu
	fname : db "data-a5.txt", 0
	errorMsg : db "File Not Found", 0xA
	errorLen : equ $-errorMsg
	linemsg : db "No. Of lines : "
	linelen : equ $-linemsg
	spacemsg : db "No. Of spaces : "
	spacelen : equ $-spacemsg
	charmsg : db "No. of times character appears : "
	charlen : equ $-charmsg
	global chars, lines, spaces
	chars : db 0
	lines : db 0
	spaces : db 0
section .bss
	global character, buffer, bufferlen
	character resb 2
	opt resb 2
	fd resb 8
	buffer: resb 200
	bufferlen: resq 1

section .text
	
global _start:
	extern hextoascii, countspaces, countlines, countchar
_start:
;------------------------Display Menu and take option--------------------
	openFile fname
	mov qword[fd], rax
	bt rax, 63
	jc fileError

	readFile [fd], buffer, 200
	mov [bufferlen], rax	;rax contains length of the file in bytes

	print menu, menulen
	input opt, 2
	print nl, 1
	mov al, byte[opt]
	cmp al, 31h
	jz case1
	cmp al, 32h
	jz case2
	cmp al, 33h
	jz case3
	cmp al, 30h
	jz case0
	
case1:		
	print spacemsg, spacelen
	call countspaces
	print nl, 1
	exit
case2:
	print linemsg, linelen
	call countlines
	print nl, 1
	exit
case3:
	print msg, msglen
	input character, 2
	print nl, 1
	print charmsg, charlen
	call countchar
	print nl, 1
	exit
fileError:
	print errorMsg, errorLen
case0:
	exit	
	
	
	
	
	
	
	
	
	
	
