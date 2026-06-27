MYCODE segment 'CODE' 
assume cs:MYCODE, ds:data 
data segment 
data ends 
start: 
    NoParamsStr DB 'Not parems$' 
    first1 db 'A' 
    first2 db 'A' 
    second1 db 'A' 
    second2 db 'A' 
    f db 0 
    filtr1 db 0 
    filtr2 db 0 
    filtr3 db 0 
    dela db 0 
    delb db 0 
    mov AX, data 
    mov ES, AX 

main: 
    mov SI, 80h 
    mov CL, [SI] 
    cmp CL, 0 
    jne contu 
    push ES 
    pop DS 
    mov DX, offset NoParamsStr 
    call printstr 
    call exit
 
contu: 
    sub CL, 1 
    add SI, 2 
    mov SI, 79h 

input: 
    inc SI 
    mov AL, [SI] 
    cmp al, '0' 
    jb input 
    cmp al, '9' 
    ja input 

    cmp first1, 'A' 
    je vvod1 
    cmp first2, 'A' 
    je vvod2 
    cmp second1, 'A' 
    je vvod3 
    cmp second2, 'A' 
    je vvod4 

con: 
    loop input 
    call clrf 
    jmp get_all_numbers 


; ===========
; Пока
; ===========
cona: 
jmp vivod 
conal: 
mov al, 0 
mov ah, 4ch 
int 021h 


; ===============
; Обработчка цифр
; ===============
vvod1 proc 
    mov first1, al 
    sub first1, 48 
    jmp con 
vvod1 endp 

vvod2 proc 
    mov first2, al 
    sub first2, 48 
    jmp con 
vvod2 endp 

vvod3 proc 
    mov second1, al 
    sub second1, 48 
    jmp con 
vvod3 endp 

vvod4 proc 
    mov second2, al 
    sub second2, 48 
    jmp con 
vvod4 endp 

; ===================
; Все 4 цифры готовы.
; ===================
get_all_numbers: 
    mov al, second2 
    add first2, al 
    mov al, first2 
    mov filtr1, al 
    cmp filtr1, 9 ; складываю последнии числа и если они больше 10 то сохр десяток
    ja telo1 


telos1: 
    mov al, delb 
    sub filtr1, al 
    mov al, dela 
    add first1, al 
    mov dela, 0 
    mov delb, 0 
    mov al,second1 
    add first1, al 
    mov al, first1 
    mov filtr2, al 
    cmp filtr2, 9 
    ja telo2 


telos2: 
    mov al, delb 
    sub filtr2, al 
    mov al, dela 
    add filtr3, al 
    mov dela, 0 
    mov delb, 0 
    jmp cona 


telo1 proc 
    mov dela, 1 
    mov delb, 10 
    jmp telos1 
telo1 endp 


telo2 proc 
    mov dela,1 
    mov delb,10 
    jmp telos2 
telo2 endp 

vivod: 
    cmp filtr3, 1 
    je dop 

vivoda: 
    add filtr2, 48 
    mov dl, filtr2 
    call putch 
    add filtr1, 48 
    mov dl, filtr1 
    call putch 
    jmp conal 

dop proc 
    mov dl, '1' 
    call putch 
    jmp vivoda 
dop endp 


getch proc 
    mov ah, 08h 
    int 021h 
    ret 
getch endp 


putch proc 
    mov ah, 02h 
    int 021h 
    ret 
putch endp 


printstr proc 
    mov ah, 09h 
    int 021h 
    ret 
printstr endp


clrf proc 
    mov dl, 10 
    call putch 
    mov dl, 13 
    call putch 
    ret 
clrf endp 

proc exit 
    mov al, 0 
    mov ah, 4ch 
    int 021h 
endp exit 


MYCODE ends 
end start
