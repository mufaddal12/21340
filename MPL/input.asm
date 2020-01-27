section .data

count db 5h
newline db 0xa
maxlen db 20h


section .bss

name: resb 32
length: resb 1

section .text

global _start
_start:

;Take input
	mov eax, 03
	mov ebx, 00
	mov ecx, name
	mov edx, 32
	int 80h

;Find length
	dec al
	cmp al, 09h
	jbe x
	add al, 07h
x : 	add al, 30h
	mov byte[length], al
	int 80h

;Display length
	mov eax, 04
	mov ebx, 01
	mov ecx, length
	mov edx, 1
	int 80h
	
	mov eax, 04
	mov ebx, 01
	mov ecx, 0xa
	mov edx, 2
	int 80h

	mov eax, 04
	mov ebx, 01
	mov ecx, newline
	mov edx, 1
	int 80h

;Display count times
label1:
	mov eax, 04
	mov ebx, 01
	mov ecx, name
	mov edx, 32
	int 80h
	
	dec byte[count]
	jnz label1
	
	
	mov eax, 01
	mov ebx, 00
	int 80h 
