section .data

str: db "Hello World", 0xA
len: equ $-str

section .text

global _start
_start:

mov rax,01
mov rdi,01
mov rsi,str
mov rdx, len
syscall

mov rax,60
mov rdi,00
syscall
