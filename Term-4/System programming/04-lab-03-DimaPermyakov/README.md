# Laboratory work 3.

## Main task:
```assembly
mycode SEGMENT 'code'
 assume cs:mycode, ds:mycode
main proc

push cs 
pop ds

mov dl, 'A'
call displ
call crlf
mov dl, 'B'
call displ
call crlf
mov dl, 'C'
call displ
call crlf

; Вывод с ожиданием.
call kbin
mov al, 0
mov ah, 4ch
int 21h
main endp
;---------
; Вывод символа.
;---------
displ proc
 mov ah, 2
 int 21h
 ret
displ endp
;---------
; Ожидание
;---------
kbin proc
 mov ah, 08h
 int 21h
 mov ah, 2
 mov dl, al
 int 21h
 ret
kbin endp
;---------
; Перенос строки
;---------
crlf proc
 mov dl, 0Ah
 call displ
 mov dl, 0Dh
 call displ
 ret
crlf endp

mycode ends
end main

```
## Adding task:
```assembly
mycode SEGMENT 'code'
 assume cs:mycode, ds:mycode
main proc

push cs 
pop ds

mov cx, 10
word db 'C'
siu: 
mov dl, word
call displ
call crlf
dec word
loop siu

; Вывод с ожиданием.
 call kbin
 mov al, 0
 mov ah, 4ch
 int 21h
main endp
;---------
; Вывод символа.
;---------
displ proc
 mov ah, 2
 int 21h
 ret
displ endp
;---------
; Ожидание
;---------
kbin proc
 mov ah, 08h
 int 21h
 mov ah, 2
 mov dl, al
 int 21h
 ret
kbin endp
;---------
; Перенос строки
;---------
crlf proc
 mov dl, 0Ah
 call displ
 mov dl, 0Dh
 call displ
 ret
crlf endp

mycode ends
end main

```