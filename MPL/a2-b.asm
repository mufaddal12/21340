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
	arr1 dq 10h, 20h, 30h, 40h, 50h, 00h, 00h, 00h, 00h, 00h
	nonoverlapdisp: db "Non-Overlapping transfer:", 0xA ;26
	overlapdisp: db "Overlapping transfer:", 0xA ;22
	menu db 0xA, 0xA,
	db "1. Non-Overlapping (Without String operation", 0xA,
	db "2. Overlapping (Without String operation", 0xA,
	db "3. Non-Overlapping (With String operation", 0xA,
	db "4. Overlapping (With String operation", 0xA,
	db " Select an option : ", 0xA
	lenmenu equ $-menu
	n: dq 05 
	digits: db 16	
	disp1: db "array 1 : ", 0xA ;11
	disp2: db "array 2 : ", 0xA
	nl: db 0xA
	sep: db " : "
	index: db 00

section .bss

	arr2 resq 5
	element resb 16
	offset resb 2
	lastindex resq 1


section .text
global _start
_start:
print menu, lenmenu
;Block transfer from arr1 to arr2 - non overlap
	print nonoverlapdisp, 26
	mov rsi, arr1
	mov rdi, arr2
	cld
	mov rcx, [n]
	rep movsq
	
	print disp1, 11
	mov r8, arr1
	mov bl, byte[n]
	mov byte[index], bl
	call printarr
	
	print disp2, 11
	mov r8, arr2
	mov bl, byte[n]
	mov byte[index], bl
	call printarr

	print nl, 1

;Overlap block transfer

	print overlapdisp, 22
	mov rsi, [n]

	input offset, 2
	
	mov al, [offset]
	sub al, 30h
	mov [offset], al

	mov rsi, arr1
	mov rdi, arr1
	add rsi, 32
	add rdi, 32
	mov al, 8
	mov bl, [offset]
	mul bl
	and rax, 0xFFFF
	add rdi, rax
	std
	mov rcx, [n]
	rep movsq
		
	mov cl, 5
	add cl, [offset]
	mov byte[index], cl
	mov r8, arr1
	call printarr
	
	exit

htoa:
	mov rsi, element
	mov cl, byte[digits]
	htoaloop:
		rol rax, 04
		mov bl, al
		and bl, 0xF
		cmp bl, 09
		jbe x
		add bl, 07
	x:	add bl, 30h
		mov byte[rsi], bl
		inc rsi
		dec cl
		jnz htoaloop	
ret

printarr:
	arrloop:
		mov rax, r8
		call htoa
		print element, 16

		print sep, 3

		mov rax, qword[r8]
		call htoa
		print element, 16

		print nl, 1
		
		add r8, 8
		dec byte[index]
		jnz arrloop
		
ret













