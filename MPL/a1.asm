section .data

	size: db 05
	arr: db 95h, 10h, 12h, 86h, 00h
	neg: db 00h
	pos: db 00h
	nl: db 0xA

section .text
global _start
_start:

;count neg/pos
	;mov cl, byte[size]
mov esi, arr
up:	
	mov al, byte[esi]
	add al, 0h
	js addneg
	
	;pos += 1 
	
	inc byte[pos]
	
	jmp label
	
	;neg += 1
addneg:	inc byte[neg]
	

label: 	inc esi
	dec byte[size]
	jnz up


;convert to ascii
	mov al, byte[pos]
	cmp al, 09H
	jbe l1
	add al, 07h
l1:	add al, 30h
	mov byte[pos], al

	mov al, byte[neg]
	cmp al, 09H
	jbe l2
	add al, 7h
l2:	add al, 30h
	mov byte[neg], al

;display

	mov eax, 04
	mov ebx, 01
	mov ecx, pos
	mov edx, 1
	int 80h
	
	mov eax, 04
	mov ebx, 01
	mov ecx, nl
	mov edx, 1
	int 80h

	mov eax, 04
	mov ebx, 01
	mov ecx, neg
	mov edx, 1
	int 80h

	mov eax, 04
	mov ebx, 01
	mov ecx, nl
	mov edx, 1
	int 80h

	mov eax, 01
	mov ebx, 00
	int 80h 



