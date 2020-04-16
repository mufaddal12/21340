;Problem Statement: Write x86 ALP to perform non-overlapped and overlapped block transfer (with and without 
;string specific instructions). Block containing data can be defined in the data segment.

;----------------------------------------------------overlapping--------------------------------------------------------

%macro print 2
	mov rax,1
	mov rdi,1
	mov rsi,%1
	mov rdx,%2
	syscall
%endmacro

%macro read 2
	mov rax,0
	mov rdi,0
	mov rsi,%1
	mov rdx,%2
	syscall
%endmacro	


section .data
	
	msgInit: db 10d,"Enter number of elements: "
	lenInit: equ $-msgInit
	
	msgGetArr: db 10d, "Enter elements: "
	lenGetArr: equ $-msgGetArr
	
	menu db 10d,13d,"MENU"
     	db 10d,"1. Non-Overlapping (Without String Instructions)"
     	db 10d,"2. Overlapping (Without String Instructions)"
     	db 10d,"3. Non-Overlapping (With String Instructions)"
     	db 10d,"4. Overlapping (With String Instructions)"
     	db 10d,"5. Exit"
     	db 10d
     	db 10d,"Enter your choice: "
	lnmenu equ $-menu    

	array db 10h,20h,30h,40h,50h
     
 	msgPutArr: db 10d,'Initial array :',0xa
 	lenPutArr: equ $-msgPutArr

	msg_no: db 10d, 'Non-Overlapping array :',0xa
 	len_no: equ $-msg_no

 	msg_o: db 10d,'Overlapping array :',0xa
 	len_o: equ $-msg_o
 	
 	msg_sno: db 10d, 'Non-Overlapping array (with string instructions):',0xa
 	len_sno: equ $-msg_sno
 	
 	msg_so: db 10d, 'Overlapping array (with string instructions):',0xa
 	len_so: equ $-msg_so
 	
 	msg_off: db 10d, 'Enter Offset: '
 	len_off: equ $-msg_off
 	
 	off dq 03h

        msg3: db ' ',0xa
 	len3: equ $-msg3
     
        msg4: db ' : '
 	len4: equ $-msg4
     
        count  db 0
        h2a1cntr db 0
        h2a2cntr db 0

section .bss
 	addr resb 16
        num1 resb 2
	arrlen resb 2
	choice resb 2
	
       
section .text
	global _start
_start:
     
;--------------------------------------Printing "Before Overlapping" message"-------------------------------------------
		
	print msgPutArr,lenPutArr
	xor rsi,rsi		;Clearing rsi array		  
	mov rsi,array		;Moving address of array to rsi
	mov byte[count],05	;Count variable stores the element count of the array
		  
;--------------------------------------Loop to print addr and value in array--------------------------------------------
	 
up:      
	mov rbx,rsi		;Moving the address of rsi(i.e Address of array) in rbx
	push rsi		;Push the address of rsi into stack
	mov rdi,addr		;Moving the value of address of addr to rdi
	call HtoA1		;Calling hex to ascii prcoedure for printing address
	pop rsi			;Retrieving the address of rsi from the stack
	mov dl,[rsi]		;Moving the value present at rsi into the stack
	push rsi		;Pushing the value of rsi again into the stack
	mov rdi,num1		;Moving 16 to rdi
	call HtoA2		;Calling hex to ascii for printing value
	pop rsi	
	inc rsi
	dec byte[count]
	jnz up

;------------------------------------------------------End Loop---------------------------------------------------------

;--------------------------------------------------------Menu-----------------------------------------------------------
	
	print menu,lnmenu
	read choice,2
	
	cmp byte[choice],'1'
        je case1
        cmp byte[choice],'2'
        je case2
        cmp byte[choice],'3'
        je case3
        cmp byte[choice],'4'
        je case4
        cmp byte[choice],'5'
        je exit

;-----------------------------------------------CASE-1 non-overlapping--------------------------------------------------

case1:
	mov rsi,array		;Moving the address of array once again into rsi(Source index)
	mov rdi,array+5h	;Moving the non-overlapping address into the destination index
	mov byte[count],05h	;Moving the number of elements of array into count variable

loopc1:	 
	mov al, byte[rsi]
	mov byte[rdi], al
	inc rsi
	inc rdi
	dec byte[count]
	jnz loopc1
	print msg_no,len_no
	mov rsi,array+5		;Moving the address of array into rsi
	mov byte[count],5h	;Moving the count of all elements into count
	
	jmp up1
	
;------------------------------------------------CASE-2 overlapping-----------------------------------------------------
case2:
	print msg_off,len_off	;Enter offset:
	read off,1		;Read offset
	
	sub byte[off],30h	;Ascii to Hex
	mov rsi,array		;Point rsi to base addr of arr
	mov rdi,array		;Point rdi to base addr of arr
	mov rax,[off]		;Add offset to rax
	add rdi,rax		;Add rax to rdi
	add rsi,04h		;Point rsi to end of array
	add rdi,04h		;Point rsi to end of array + offset
	mov byte[count],05h	;Moving the number of elements of array into count variable

loopc2:	 
	mov al, byte[rsi]
	mov byte[rdi], al
	dec rsi
	dec rdi
	dec byte[count]
	jnz loopc2
	print msg_o,len_o
	mov rsi,array		;Moving the address of array into rsi
	
	add byte[count],05h
	mov al,byte[off]
	add byte[count],al	;Moving size of array + offset to count
	
	jmp up1 

;--------------------------------------------CASE-3 string non-overlapping----------------------------------------------
case3:
	mov rsi,array		;Moving the address of array once again into rsi(Source index)
	mov rdi,array+5h	;Moving the non-overlapping address into the destination index
	mov byte[count],05h	;Moving the number of elements of array into count variable

loopc3:	 
	movsb
	dec byte[count]
	jnz loopc3
	print msg_sno,len_sno
	mov rsi,array+5		;Moving the address of array into rsi
	mov byte[count],5h	;Moving the count of all elements into count 
	
	jmp up1

;-----------------------------------------------CASE-4 string overlapping----------------------------------------------
case4:
	print msg_off,len_off	;Enter offset:
	read off,1		;Read offset
	
	sub byte[off],30h	;Ascii to Hex
	mov rsi,array		;Point rsi to base addr of arr
	mov rdi,array		;Point rdi to base addr of arr
	mov rax,[off]		;Add offset to rax
	add rdi,rax		;Add rax to rdi
	add rsi,04h		;Point rsi to end of array
	add rdi,04h		;Point rsi to end of array + offset
	mov byte[count],05h	;Moving the number of elements of array into count variable
	std
loopc4:	 
	movsb
	dec byte[count]
	jnz loopc4
	
	print msg_so,len_so
	mov rsi,array		;Moving the address of array into rsi
	
	add byte[count],05h
	mov al,byte[off]
	add byte[count],al	;Moving size of array + offset to count
	
	jmp up1

;----------------------------------------Loop to print addr and value in array------------------------------------------
	
up1:	 
	
	mov rbx,rsi
	push rsi
	mov rdi,addr
	call HtoA1
	pop rsi
	mov dl,[rsi]
	push rsi
	mov rdi,num1
	call HtoA2
	pop rsi
	inc rsi
	dec byte[count]
	jnz up1

;----------------------------------------------Terminating the program--------------------------------------------------
exit:	
	mov rax,60
	mov rdi,0
	syscall 

;-----------------------------------------------------Procedures--------------------------------------------------------

HtoA1:
	 ;Moving 16 to h2a1cntr variable
	 	mov byte[h2a1cntr],16
	 

dup1:	 rol rbx,4
	 mov al,bl
	 and al,0fh
	 cmp al,09
	 jbe l1
	 add al,07h
l1:	 add al,30h
	 
	 mov [rdi],al
	 inc rdi
	 dec byte[h2a1cntr]
	 jnz dup1 

	 print addr,16
 
	 print msg4,len4

	 ret

HtoA2:
	 mov byte[h2a2cntr],02
	 
dup2:	 rol dl,04
	 mov al,dl
	 and al,0fh
	 cmp al,09h
	 jbe l2
	 add al,07h
l2:	 add al,30h
	 
	 mov [rdi],al
	 inc rdi
	 dec byte[h2a2cntr]
	 jnz dup2
	     
	 print num1,02

	 print msg3,len3

	 ret
