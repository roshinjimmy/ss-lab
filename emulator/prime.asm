.model small
.stack 100h

.data
    num db 13
    msg_prime db "The number is prime.$"
    msg_not_prime db "The number is not prime.$"
    buffer db "0$"

.code
start:
    mov ax, @data
    mov ds, ax

    mov al, [num]

    cmp al, 2
    jl not_prime

    mov bl, 2
    
check_divisibility:
    mov ah, 0
    div bl

    cmp ah, 0
    je not_prime

    mov dl, bl
    mul dl
    mov bx, ax
    mov al, [num]
    cmp bx, ax
    jg prime

    inc bl
    jmp check_divisibility

not_prime:
    lea dx, msg_not_prime
    mov ah, 09h
    int 21h

    jmp done

prime:
    lea dx, msg_prime
    mov ah, 09h
    int 21h

done:
    mov ah, 4Ch
    int 21h

end start
