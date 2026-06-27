MYCODE segment 'CODE' 
assume cs:MYCODE, ds:MYCODE 

HEX_STRING DB 'F E D C B A 9 8 7 6 5 4 3 2 1 0' 
Welcome DB 'Enter symbol: $' 
Quit DB 'q - QUIT CODE$' 
Dash DB '-' 
QuitSym DB 'q' 
teste db 15 
start: 
push CS 
pop DS 
mov BX, offset HEX_STRING 

main: 
mov DX, offset Welcome 
call printstr 
call clrf 

call getch 
push AX 
mov CX, 10 
cycle: 
    pop AX 
    push AX 
    push AX 
    push AX 
    push AX 
    mov DL, AL 
    call putch 

    ; ' - ' 
    mov DX, 32 
    call putch 
    mov AH, 02h 
    mov DL, Dash 
    INT 21H 
    mov DX, 32 
    call putch 

    pop AX 
    call hex 
    pop AX 

    ; ' - ' 
    mov DX, 32 
    call putch 
    mov DX, 32 
    call putch 

    call clrf 
    pop AX 

    inc AL 
    push AX 

loop cycle 

mov DX, offset Quit 
call printstr 
call clrf 
call getch 
cmp AL, QuitSym 
je exit 
jmp main 

exit: 
    mov al, 00 
    mov ah, 4ch 
    int 021h 


; print string 
printstr proc 
    mov ah, 09h 
    int 021h 
    ret 
printstr endp 


putch proc 
    mov ah, 02h 
    int 021h 
    ret 
putch endp 


getch proc 
    mov ah, 08h 
    int 021h 
    ret 
getch endp 


; /n/r 
clrf proc 
    mov dl, 10 
    call putch 
    mov dl, 13 
    call putch 
    ret 
clrf endp 

hex proc 
    push AX 
    shr al, 4 
    sub teste, al 
    mov al, teste 
    add al, al 
    xlat 
    mov teste, 15 
    mov dl, al 
    call putch 
    pop ax 
    and al, 00001111b 
    sub teste, al 
    mov al, teste 
    add al, al 
    xlat 
    mov dl, al 
    mov teste, 15 
    call putch 
    mov dx, 104 
    call putch 
    ret 
hex endp 


MYCODE ends 
end start 