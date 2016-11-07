%include "io.inc"

struc stud_struct
    name: resb 32
    surname: resb 32
    age: resb 1
    group: resb 8
    gender: resb 1
    birth_year: resw 1
    id: resb 16
endstruc

section .data

sample_student:
    istruc stud_struct
        at name, db 'Andrei', 0
        at surname, db 'Voinea', 0
        at age, db 21
        at group, db '321CA', 0
        at gender, db 1
        at birth_year, dw 1994
        at id, db 0
    iend

string_id db "ID: ", 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov al, [sample_student + name]
    mov [sample_student + id], al
    mov al, [sample_student + surname]
    mov [sample_student + id + 1], al
    mov byte [sample_student + id + 2], 0

    PRINT_STRING string_id
    PRINT_STRING [sample_student + id]
    NEWLINE

    leave
    ret
