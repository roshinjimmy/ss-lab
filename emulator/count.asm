DATA SEGMENT
    MSG1 DB 10, 13, "Enter the number of elements: $"
    MSG2 DB 10, 13, "Enter each number followed by ENTER: $"
    MSG3 DB 10, 13, "Even count: $"
    MSG4 DB 10, 13, "Odd count: $"
    STR1 DB 50 DUP(0)
    EVEN_COUNT DB 0
    ODD_COUNT DB 0
DATA ENDS

CODE SEGMENT
ASSUME CS: CODE, DS: DATA
START:
    MOV AX, DATA
    MOV DS, AX

    ; Prompt user for number of elements
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    ; Read number of elements
    MOV AH, 01H
    INT 21H
    SUB AL, '0'        ; Convert ASCII to integer
    MOV CL, AL         ; Store count in CL

    ; Prompt user to enter each number
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    MOV SI, 0          ; Index for STR1 array
    MOV EVEN_COUNT, 0  ; Initialize even count
    MOV ODD_COUNT, 0   ; Initialize odd count

READ_NUMBERS:
    MOV AH, 01H        ; Read a character
    INT 21H
    CMP AL, 0DH        ; Check for ENTER key (carriage return)
    JE CHECK_PARITY
    SUB AL, '0'        ; Convert ASCII to integer
    MOV STR1[SI], AL   ; Store the number in STR1
    INC SI             ; Move to next position
    LOOP READ_NUMBERS

CHECK_PARITY:
    MOV CX, SI         ; Move number of entries in CX for loop
    MOV SI, 0          ; Reset index for STR1 array

COUNT_EVEN_ODD:
    MOV AL, STR1[SI]   ; Load number from STR1
    TEST AL, 1         ; Check if the number is even or odd
    JNZ ODD_NUMBER     ; Jump if the number is odd
    INC EVEN_COUNT     ; Increment even count
    JMP NEXT_NUMBER

ODD_NUMBER:
    INC ODD_COUNT      ; Increment odd count

NEXT_NUMBER:
    INC SI             ; Move to next number
    LOOP COUNT_EVEN_ODD

    ; Display even count
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H
    MOV AL, EVEN_COUNT
    ADD AL, '0'        ; Convert to ASCII
    MOV DL, AL
    MOV AH, 02H
    INT 21H

    ; Display odd count
    LEA DX, MSG4
    MOV AH, 09H
    INT 21H
    MOV AL, ODD_COUNT
    ADD AL, '0'        ; Convert to ASCII
    MOV DL, AL
    MOV AH, 02H
    INT 21H

    ; Exit program
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START