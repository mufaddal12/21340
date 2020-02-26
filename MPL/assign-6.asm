%macro print 2
	mov rax, 01
	mov rdi, 01
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
	gmsg: db 0x0A,"Contents of GDTR : "
	gmsg_len: equ $-gmsg
	lmsg: db 0x0A,"Contents of LDTR : "
	lmsg_len: equ $-lmsg
	imsg: db 0x0A,"Contents of IDTR : "
	imsg_len: equ $-imsg
	tmsg: db 0x0A,"Contents of TR : "
	tmsg_len: equ $-tmsg
	mmsg: db 0x0A,"Contents of MSW : "
	mmsg_len: equ $-mmsg
	realmsg: db "---- In Real mode. ----"
	realmsg_len: equ $-realmsg
	protmsg: db "---- In Protected Mode. ----"
	protmsg_len: equ $-protmsg
	cnt2:db 04H
	nl: db 0x0A

section .bss
	g:	resd 1
	l:	resw 1
	idtr:	resd 1
	msw:	resd 1
	tr:	resw 1
	result : resb 4

section .txt
global _start

_start:

;print if real or protected
	smsw [msw]
	mov eax, dword[msw]
	bt eax, 0
	jc prot
	print realmsg, realmsg_len
	exit
prot:	print protmsg, protmsg_len
	print nl, 1

;printing contents of GDTR
	print gmsg, gmsg_len
	sgdt [g]
	mov ax, word[g+4]
	call HtoA
	mov ax, word[g+2]
	call HtoA
	mov ax, word[g]
	call HtoA

;printing content of LDTR
	print lmsg, lmsg_len
	sldt [l]
	mov ax,word[l]
	call HtoA

;printing content of IDTR
	print imsg, imsg_len
	sidt [idtr]
	mov ax, word[idtr+4]
	call HtoA
	mov bx,word[idtr+2]
	call HtoA
	mov ax, word[idtr]
	call HtoA

;printing contents of TR
	print tmsg, tmsg_len
	str [tr]
	mov ax, word[tr]
	call HtoA

;printing contentes of MSW
	print mmsg, mmsg_len
	mov ax, word[msw]
	call HtoA
	print nl, 1
	exit

HtoA:
	mov rsi, result
	mov cl, 04
	loop3:
		rol ax, 04h
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
	print result, 4
ret









