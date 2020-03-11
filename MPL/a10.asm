extern scanf, printf

%macro write 3
	mov rax, 01
	mov rdi, %1
	mov rsi, %2
	mov rdx, %3
	syscall
%endmacro

%macro myscanf 1
	mov rdi, format1
	sub rsp, 8
	mov rax, 0
	mov rsi, rsp
	call scanf
	mov r8, [rsp]
	mov [%1], r8
	add rsp, 8
%endmacro

%macro myprintf 1
	mov rdi, format
	sub rsp, 8
	movsd xmm0, [%1]
	mov rax, 1
	call printf
	add rsp, 8
%endmacro

%macro exit 0
	mov rax, 60
	mov rdi, 00
	syscall
%endmacro

section .data
	format db "%lf", 0xA , 0
	format1 db "%lf", 0
	x2msg db "Coeff of X^2 : "
	x2len: equ $-x2msg

	x1msg db "Coeff of X^1 : "
	x1len: equ $-x1msg

	x0msg db "Coeff of X^0 : "
	x0len: equ $-x0msg

	four dd 4
	two dd 2
section .bss
	a: resq 1
	b: resq 1
	c: resq 1
	D: resq 1

section .txt
global main

main:
	write 01, x2msg, x2len
	myscanf a

	write 01, x1msg, x1len

	myscanf b
	write 01, x1msg, x1len
	myscanf c
	
	finit

	;b^2
	fld qword[b]
	fmul st0

	;4ac
	fld qword[a]
	fimul dword[four]
	fmul qword[c]

	;b^2 - 4ac
	fsub
	fst qword[D]
	myprintf D
	mov rax, qword[D]
	bt rax, 63
	jc imaginary
	exit
imaginary:
	fld qword[D]
	fsqrt
	fst qword[D]
	myprintf D
	exit



