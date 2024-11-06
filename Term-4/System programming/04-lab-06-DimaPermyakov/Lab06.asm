
MYDATA SEGMENT 'DATA'
	HEX_STRING DB '0123456789'
	STROKE db 20 dup('-'),'$'
	
MYDATA ENDS

mycode SEGMENT 'code'

assume cs:mycode, ds:mycode
	start:
	mov cl, ds:80h ; кол-во байт
	push cx
	mov di,81h

	get_param:
		mov al,[di]    ; берем по символу
		add di,1

		mov dl,al
		mov ah, 2
		int 21h
		
		cmp al, ' '
		jne not_equal
		inc bx 		    ; кол-во слов

		not_equal:
	loop get_param
	
	pop cx
	mov dh,cl
	mov AX, MYDATA
	mov DS, AX
	push ds
	pop es	
	call crlf
	call hex

	mov al, 0
	mov ah, 4ch
	int 21h

	translatee proc 
		del:
		mov bl,10
		div bl
		cmp al,0
		je write
		mov [di],ah
		mov ah,0
		inc di
		loop del
		write:
		mov [di],ah
		reverse:
		mov al,[di]
		add al,'0'
		mov dl,al
		mov ah,2
		int 21h
		dec di
		mov al,'*'
		cmp [di],al
		je exit_one
		loop reverse
		exit_one:
		inc di
		ret
	translatee endp

	hex proc
		lea di,STROKE
		mov al,'*'
		mov [di],al
		inc di
		mov ax,bx
		call translatee
		call crlf
		mov ax,cx
		call translatee
		ret
	hex ENDP;

	crlf proc
		MOV AH,02
		MOV DL,13
		INT 21H
		MOV AH,02
		MOV DL,10
		INT 21H
		RET
	crlf ENDP;

mycode ENDS
END start
