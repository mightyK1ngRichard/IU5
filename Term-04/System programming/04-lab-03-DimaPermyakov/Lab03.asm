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

;mov dl, 'A'
 ;call displ
 ;call crlf
;mov dl, 'B'
; call displ
 ;call crlf
;mov dl, 'C'
; call displ
; call crlf

; ????? ? ?????????.
 call kbin
 mov al, 0
 mov ah, 4ch
 int 21h
main endp
;---------
; ????? ???????.
;---------
displ proc
 mov ah, 2
 int 21h
 ret
displ endp
;---------
; ????????
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
; ??????? ??????
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
