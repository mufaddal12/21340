%macro print 2
	mov eax, 04
	mov ebx, 01
	mov ecx, %1
	mov edx, %2
	int 80h
%endmacro

section .data
	arr: db 10h, 15h, 25h, 67h, 30h
	size: db 05
	digs: db 02
	disp: db 00
	space: db " "
	value: db 00
	address: dw 00
section .text
global _start

_start:
	mov esi, arr

;loop through elemens of array
outerloop:
	mov bl, byte[esi]
	mov byte[value], bl
	mov byte[digs], 2

;loop through digits of an element for printing
	printing:
		mov bl, byte[value]
		rol bl, 04
		mov byte[value], bl
		and bl, 0x0f
		cmp bl, 09h
		jbe x
		add bl, 07h
	x:	add bl, 30h
		
		mov byte[disp], bl
	
	;print the digit
		print disp, 1

		dec byte[digs]
		jnz printing
	
	print space, 1
	
	inc esi
	dec byte[size]
	jnz outerloop

	mov eax, 01
	mov ebx, 00
	int 80h
		





		
