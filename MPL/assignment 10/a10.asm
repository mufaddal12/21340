extern scanf, printf

%macro write 2
        mov rax,1
        mov rdi,1
        mov rsi,%1
        mov rdx,%2
        syscall
%endmacro

%macro myscanf 1
	mov rdi, formatsf
	sub rsp, 8
	mov rax, 0
	mov rsi, rsp
	call scanf
	mov r8, qword[rsp]
	mov qword[%1], r8
	add rsp, 8
%endmacro

%macro myprintf 1
	mov rdi, formatpf
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
	formatpf db "%lf", 0xA , 0
	formatsf db "%lf", 0

	x2msg db "Coeff of X^2 : "
	x2len: equ $-x2msg

	x1msg db "Coeff of X^1 : "
	x1len: equ $-x1msg

	x0msg db "Coeff of X^0 : "
	x0len: equ $-x0msg

	msgeq db "Equation : ",
        leneq equ $-msgeq

	msgr1 db "First root, x1 = ",
        lenr1 equ $-msgr1
        
        msgr2 db "Second root, x2 = ",
        lenr2 equ $-msgr2

	ff1: db "%lf +i %lf",10,0
        ff2: db "%lf -i %lf",10,0
        
        ff3: db "%lfx² + %lfx + %lf = 0",10,0

	four dq 4
	two dq 2
section .bss
	a: resq 1
	b: resq 1
	c: resq 1
	D: resq 1
	rD: resq 1
	b2: resq 1
	ta: resq 1
	r1: resq 1
	r2: resq 1
	fac: resq 1
	img1: resq 1
	img2: resq 1
	realn: resq 1
	
	
section .txt
global main

main:
	write x2msg, x2len
	myscanf a
	write x1msg, x1len
	myscanf b
	write x1msg, x1len
	myscanf c
	
	write msgeq, leneq
                
        mov rdi,ff3
        sub rsp,8
        movsd xmm0,[a]
        movsd xmm1,[b]
        movsd xmm2,[c]
        mov rax,3
        call printf
        add rsp,8

	;b^2
	fld qword[b]
	fmul qword[b]
	fstp qword[b2]

	;4ac
	fild qword[four]
	fmul qword[a]
	fmul qword[c]
	fstp qword[fac]

	;b^2 - 4ac
	fld qword[b2]
	fsub qword[fac]
	fstp qword[D]
	
	;2a
	fild qword[two]
	fmul qword[a]
	fstp qword[ta]

	btr qword[D],63 
        jc imaginary

	;real roots
	
	fld qword[D]
	fsqrt
	fstp qword[rD]
	
	;printing first real root
	write msgr1, lenr1
	
	fldz
	fsub qword[b]
	fadd qword[rD]
	fdiv qword[ta]
	fstp qword[r1]
	myprintf r1

	write msgr2, lenr2
	
	fldz
	fsub qword[b]
	fsub qword[rD]
	fdiv qword[ta]
	fstp qword[r2]
	myprintf r2
	exit

imaginary:
	fld qword[D]
	fsqrt
	fstp qword[rD]
	
	fldz
	fld qword[b]
	fdiv qword[ta]
	fstp qword[realn]

	fld qword[rD]
	fdiv qword[ta]
	fstp qword[img1]

	;printing first imaginary root
	write msgr1, lenr1
	
	mov rdi,ff1
        sub rsp,8

	movsd xmm0,[realn]
        movsd xmm1,[img1]
	mov rax,2
        call printf
        add rsp,8

	;printing second imaginary root
	write msgr2, lenr2
	
	mov rdi,ff2
        sub rsp,8

	movsd xmm0,[realn]
        movsd xmm1,[img1]
	mov rax,2
        call printf
        add rsp,8

	exit



