data segment
    arr db 10, 11, 12, 13, 14, 15, 16, 9  
    size db 08                          
    msg1 db 10,13, "Number of odd numbers is: $"
    buffer db "0$"                     
data ends

code segment
    assume cs:code ds:data

start:
    mov ax, data
    mov ds, ax                          

    lea si, size
    mov cl, [si]                        
    lea si, arr                         
    mov bl, 0                           

next:
    cmp cl, 0                            
    je print

    mov al, [si]                        
    test al, 01                          
    jz even                              

    inc bl                               
even:
    inc si                               
    dec cl                               
    jmp next

print:
    lea dx, msg1                         
    mov ah, 09h                          
    int 21h

    mov al, bl                           
    add al, '0'                          
    mov [buffer], al                     

    lea dx, buffer                       
    mov ah, 09h                          
    int 21h

xx:
    mov ah, 4Ch                          
    int 21h

code ends
end start
