; на случай если я забыл свою идею. я читаю строку с конца а hex выводит наоборот

assume cs:CODE
CODE SEGMENT 'CODE'
; ------------------------------- 
LABTITLE DB 'Laboratory work #5$'
HELP1 DB 'New world - enter$'
HELP2 DB 'Stop code - esc$'
ESCSMBL DB 27 ; esc
ENTRSMBL DB 13 ; enter
; -------------------------------
HEX_TABLE DB '0123456789ABCDEF'
CURNTSMBL DB 'A'
STRING db 41 dup ('$')
; -------------------------------
START:
     push cs
     pop  ds
     call CLRSCR
     call CLRF
     mov dx , offset LABTITLE
     call PUTSTR
     call CLRF
     call CLRF
     mov dx , offset HELP1
     call PUTSTR
     call CLRF
     mov dx , offset HELP2
     call PUTSTR
     call CLRF
     call CLRF
     MAIN:
       mov si , 0
       mov cx , 40
       INPUTSTR:
          call GETCH
          mov CURNTSMBL , al
          cmp al , ESCSMBL
          je EXITP
          cmp al , ENTRSMBL
    			je FINDEND
          mov dl , al
          call PUTCH
          mov bh , CURNTSMBL
    			mov STRING[si] , bh
    			inc si
          loop INPUTSTR
     FINDEND:
       mov cx , si
       dec si ; моя фича
       ;mov si , 0
       mov dl , ' '
       call PUTCH
       mov dl , '='
       call PUTCH
       OUTPUTCH:
         mov dl , ' '
         call PUTCH
         mov bh , STRING[si]
         mov CURNTSMBL , bh
         mov dl , 'h'
         call PUTCH
         call HEX
         ;inc si
         dec si ; моя фича
         ; -mov dl , 'h'
         ; -call PUTCH
         loop OUTPUTCH
       call CLRF
       dec di
   		 mov cx , di

       loop MAIN
     EXITP:
       mov al , 0
       mov ah , 4CH
       int 21H

; -------------------------------

HEX PROC
    ; Выводим младший байт вначале
    mov dl, CURNTSMBL
    mov al, dl
    and al, 00001111b 
    lea bx, HEX_TABLE
    xlat 
    mov dl, al
    call PUTCH

    ; Выводим старший байт
    mov dl, CURNTSMBL
    mov al, dl
    shr al, 4 
    xlat 
    mov dl, al
    call PUTCH
    ret
HEX ENDP
; -------------------------------

CLRF PROC
    mov dl , 10
    call PUTCH
    mov dl , 13
    call PUTCH
    ret
CLRF ENDP
; -------------------------------
CLRSCR PROC
    call CLRF
    mov  ah , 0H
    mov  al , 3H
    int  10H
    ret
CLRSCR ENDP
; -------------------------------
PUTCH PROC
    mov ah , 02H
    int 21H
    ret
PUTCH ENDP
; -------------------------------
PUTSTR PROC
    mov ah , 09H
    int 21H
    ret
PUTSTR ENDP
; -------------------------------
; ���� ᨬ���� � ����������
GETCH PROC
    mov ah , 08H
    int 21H
    ret
GETCH ENDP

END START
CODE ENDS