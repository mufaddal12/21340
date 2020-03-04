;printing
%macro print 2
	mov rax, 01
	mov rdi, 01
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro

;take input
%macro input 2
	mov rax, 00
	mov rdi, 00
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro


;system call
%macro exit 0
	mov rax, 60
	mov rdi, 00
	syscall
%endmacro

section .data

	arr1: dq 10h, 20h, 30h, 40h, 50h, 00h, 00h, 00h, 00h, 00h
	nonoverlapdisp: db "Non-Overlapping transfer:", 0xA ;26
	overlapdisp: db "Overlapping transfer:", 0xA ;22
	overlaps: dw 00
	size: db 05h
	digits: db 16
	disp1: db "array 1 : ", 0xA
	disp2: db "array 2 : ", 0xA
	nl: db 0xA
	sep: db " : "

section .bss
	arr2 resq 5
	element resb 16
section .text

global _start

_start:

;non-overlapping transfer	
	print nonoverlapdisp, 26	

	mov rsi, arr1
	mov rdi, arr2
	mov bl, 05h
;copying data from arr1 to arr2
	loop1:					
		mov rax, qword[rsi]
		mov qword[rdi], rax
		add rsi, 8
		add rdi, 8
		dec bl
	
		jnz loop1

;print arr1
	print disp1, 11
	mov r8, arr1
	call printarr
	
	print nl, 1
	print disp2, 11

;print arr2
	mov r8, arr2
	mov byte[size], 05h
	call printarr

	print nl, 1
;end non overlap transfer

;overlapping transfer
	print overlapdisp, 22

;overlaps input
	input overlaps, 1
	mov al, byte[overlaps]
	sub al, 30h
	mov byte[overlaps], al


;last element index	

	mov byte[size], 05
	mov rsi, [size]
	and rsi, 0xff 
	mov rbx, [overlaps]
	and rbx, 0xff
	mov r8, rsi
	sub r8, rbx
	add r8, rsi

;transfering data from arr1 to overlapped destination

	loop4:
		mov r10, qword[arr1 + rsi*8]
		mov qword[arr1 + r8*8], r10
		dec r8
		dec rsi
		jnz loop4
	mov r10, qword[arr1 + rsi*8]
	mov qword[arr1 + r8*8], r10

;print arr1

	print disp1, 11
	mov r8, arr1
	mov al, byte[size]
	sub al, byte[overlaps]
	add al, byte[size]
	mov byte[size], al
	call printarr
	exit
	
;convert hex to ascii
htoa:
	mov rsi, element
	mov cl, byte[digits]
	loop3:
		rol rax, 04h
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

;printing an array
printarr:
	loop2:
		;prints address
		mov rax, r8
		call htoa
		print element, 16
		
		print sep, 3

		;print element
		mov rax, qword[r8]
		call htoa
		print element, 16

		print nl, 1

		add r8, 8
		dec byte[size]
		jnz loop2
ret






