assume cs:code
code segment
    start:
        mov ax,0000h
        mov bx,0000h
        mov cx,0000h
        mov al,25h
        mov cl,00h
        mov bl,01h
    root:
        cmp al,00h
        jz zero
        sub al,bl
        aas
        add bl,02h
        inc cl
        jmp root
    zero:
        add cl,30h
        mov dl,cl
        mov ah,2
        int 21h
    code ends
        end start