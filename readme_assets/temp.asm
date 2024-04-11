extern malloc
extern calloc
extern strcpy

extern HashNodeCtr

section     .text
global HashTableInsert

HashTableInsert:
; -----------------------------------------------
    xor eax, eax
    vmovdqu ymm1, yword [rsi]
; -----------------------------------------------
    crc32 rax, qword [rsi +  0]
    crc32 rax, qword [rsi +  8]
    crc32 rax, qword [rsi + 16]
    crc32 rax, qword [rsi + 24]
; -----------------------------------------------
    mov rcx, qword [rdi + 8]
    dec rcx
    and rax, rcx
; -----------------------------------------------
    mov r8, qword [rdi + 16]           ; rdi - table, rsi - key, rdx - val, r8 - lst
    shl rax, 4
    add r8, rax
; -----------------------------------------------
    mov r9, qword [r8 + 8]             ; r9 - prev, r10 - curr
    mov r10, qword [r9 + 16]
; -----------------------------------------------
    xor eax, eax
; -----------------------------------------------
    test r10, r10
    je EndListIter
ListIter:
    mov r11, qword [r10]
    vmovdqu ymm0, yword [r11]
    vptest ymm0, ymm1
    jnb NextIter

    mov qword [r10 + 8], rdx
    ret
NextIter:
    mov r9, r10
    mov r10, qword [r10 + 16]

    test r10, r10
    jne ListIter
EndListIter:
; -----------------------------------------------
    push r8
    push r9
    push rdi

    mov rdi, rsi
    mov rsi, rdx
    call HashNodeCtr

    pop rdi
    pop r9
    pop r8
; -----------------------------------------------
    mov qword [r9 + 16], rax
    add qword [r8], 1
    add qword [rdi], 1
; -----------------------------------------------
    mov eax, 1
    ret
; -----------------------------------------------